/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#include "Chapter.h"

#include <windows.h>
#include <tchar.h>

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "../../../Obj.h"
#include "Section/Text/Tstring/TString.h"
#include "Section/Section.h"

VOID Chapter::ReadChapterFile(const TCHAR* pChapterTextFilePath, TString* pChapterText) const
{
	std::ifstream ifs(pChapterTextFilePath);

	std::string charsBuf;
	std::string tmp;
	while (std::getline(ifs, tmp))
	{
		charsBuf += tmp;
		charsBuf.push_back('\n');
		charsBuf.push_back('\r');
	}

	charsBuf.push_back('\0');

	size_t charsNum = charsBuf.size();
	CHAR* pCharsToTChars = new CHAR[charsNum];

	for (INT i = 0; i < charsNum; ++i)
	{
		pCharsToTChars[i] = charsBuf[i];
	}

	TCHAR* pTCharBuf = new TCHAR[charsNum];
	setlocale(LC_CTYPE, "jpn");

	size_t lengthConverted;
	mbstowcs_s(&lengthConverted, pTCharBuf, charsNum, pCharsToTChars, _TRUNCATE);

	pChapterText->WriteInAll(pTCharBuf);

	delete[] pTCharBuf;
	delete[] pCharsToTChars;
}

VOID Chapter::DevideTextsBySectionAndSet(TString* pChapterText)
{
	TCHAR buf = NULL;
	TString bufToSkip;

	for (INT i = 0; i < SD_MAX; ++i)
	{
		pChapterText->GetLine(&bufToSkip);	//! セクションタグは現状必要ないので空読み

		while (TRUE)
		{
			buf = pChapterText->GetTChar();

			if (buf == m_SECTION_TAG || buf == TString::m_TEXT_END) break;

			m_sectionsTexts[i].WriteInChar(buf);
		}

		m_sectionsTexts[i].WriteInChar(TString::m_TEXT_END);
	}
}

BOOL Chapter::ShouldOperationSection()
{
	FLOAT ratioInsertSection = static_cast<FLOAT>(m_currentSectionDetail) / (SD_MAX - 1);

	const LONGLONG m_ACCEPTABLE_M_SEC_LAG = 300;

	static LONGLONG currentStageTime = NULL;

	if (!m_isActive)
	{
		currentStageTime = m_rGameLib.GetMilliSecond();
	}

	if (static_cast<LONGLONG>(currentStageTime + m_ACCEPTABLE_M_SEC_LAG) <=
		static_cast<LONGLONG>(m_rStageMSec * ratioInsertSection)) return FALSE;
	if (m_pSections[m_currentSectionDetail]->Ends()) return FALSE;

	if (m_currentSectionDetail == SD_MIDDLE)
	{
		int i = 0;
	}

	if (!m_isActive)
	{
		m_rGameLib.StopTime();
	}

	m_isActive = TRUE;

	return TRUE;
}
