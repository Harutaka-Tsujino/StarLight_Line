/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef CHAPTER_H
#define CHAPTER_H

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

class Chapter :public Obj
{
public:
	Chapter(const TCHAR* pChapterTextFilePath, const LONGLONG& stageMSec) 
		:Obj(OT_TRANSPARENCY, 0.0f), m_rStageMSec(stageMSec)
	{
		TString chapterText;
		ReadChapterFile(pChapterTextFilePath, &chapterText);
		DevideTextsBySectionAndSet(&chapterText);

		for (INT i = 0; i < SD_MAX; ++i)
		{
			m_pSections[i] = new Section(m_sectionsTexts[i]);
		}
	}

	~Chapter()
	{
		for (auto i : m_pSections)
		{
			delete i;
		} 
	}

	inline VOID Update()
	{
		if (!ShouldOperationSection()) return;

		Section* pCurrentSecion = m_pSections[m_currentSectionDetail];

		m_pSections[m_currentSectionDetail]->Update();

		if (m_pSections[m_currentSectionDetail]->Ends()) TransNextSection();
	}

	inline VOID Render()
	{
		if (!ShouldOperationSection()) return;

		m_pSections[m_currentSectionDetail]->Render();
	}

	inline VOID TransNextSection()
	{
		m_currentSectionDetail = (m_currentSectionDetail >= SD_LAST) ? SD_LAST : ++m_currentSectionDetail;

		m_rGameLib.RestartTime();

		m_isActive = FALSE;
	}

	inline BOOL CurrentSctionEnds() const
	{
		return m_pSections[m_currentSectionDetail]->Ends();
	}

	inline BOOL AllSectionEnds() const
	{
		return m_pSections[SD_LAST]->Ends();
	}

	inline BOOL IsActive()
	{
		return m_isActive;
	}

private:
	enum SECTION_DETAIL
	{
		SD_FIRST,
		SD_MIDDLE,
		SD_LAST,
		SD_MAX
	};

	Chapter& operator=(const Chapter&) = delete;
	Chapter(const Chapter&) = delete;

	VOID ReadChapterFile(const TCHAR* pChapterTextFilePath, TString* pChapterText) const;

	VOID DevideTextsBySectionAndSet(TString* pChapterText);
	
	BOOL ShouldOperationSection();
	
	BOOL m_isActive = FALSE;

	const TCHAR m_SECTION_TAG = '#';

	std::array<TString, SD_MAX> m_sectionsTexts;
	std::array<Section*, SD_MAX> m_pSections;

	const LONGLONG& m_rStageMSec = NULL;
	
	INT m_currentSectionDetail = SD_FIRST;
};

#endif //! CHAPTER_H
