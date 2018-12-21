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
#include "Section\Text\Tstring\TString.h"
#include "Section\Section.h"

class Chapter :public Obj
{
public:
	Chapter(const TCHAR* pChapterTextFilePath) :Obj(OT_TRANSPARENCY, 1.0f)
	{

	}

	VOID TransNextSection()
	{

	}

	BOOL Ends()
	{

	}

private:
	enum SECTION_DETAIL
	{
		SD_FIRST,
		SD_MIDDLE,
		SD_LAST,
		SD_MAX
	};

	VOID DevideTextsBySectionAndSet()
	{

	}

	std::array<TString, SD_MAX> m_sectionsTexts;
	std::array<Section*, SD_MAX> m_pSections;
	INT m_currentSectionDetail = SD_FIRST;

};

#endif //! CHAPTER_H
