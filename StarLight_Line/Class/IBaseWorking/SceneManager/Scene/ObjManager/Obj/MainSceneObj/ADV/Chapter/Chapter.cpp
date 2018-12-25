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
#include "Section\Text\Tstring\TString.h"
#include "Section\Section.h"

VOID Chapter::ReadChapterFile(const TCHAR* pChapterTextFilePath, TString* pChapterText) const
{
	std::ifstream ifs(pChapterTextFilePath);

	std::vector<CHAR>charsBuf;
	CHAR tmp = NULL;
	while (ifs >> tmp) charsBuf.push_back(tmp);

	size_t charsNum = charsBuf.size();
	CHAR* pCharsToTChars = new CHAR[charsNum];
	for (INT i = 0; i < charsNum; ++i) 	pCharsToTChars[i] = charsBuf[i];

	TCHAR* pTCharBuf = new TCHAR[charsNum];
	setlocale(LC_CTYPE, "jpn");

	size_t lengthConverted;
	mbstowcs_s(&lengthConverted, pTCharBuf, sizeof(TCHAR) * charsNum, pCharsToTChars, sizeof(CHAR) * charsNum);

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
