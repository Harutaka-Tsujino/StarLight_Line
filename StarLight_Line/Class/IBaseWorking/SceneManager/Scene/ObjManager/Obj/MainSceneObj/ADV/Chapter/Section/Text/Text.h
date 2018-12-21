/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef TEXT_H
#define TEXT_H

#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "../../../../../../../../../../../GameLib/GameLib.h"
#include "Data\TextFormat.h"
#include "Tstring\TString.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

class Text
{
public:
	Text(const TString* pText, const TCHAR* pFontTexPath) :m_rGameLib(GameLib::GetInstance())
	{
		pText->WriteOutAll(&m_text);

		DivideTextByNewLine();

		if (m_rGameLib.TexExists(m_pFONT_KEY)) return;

		m_rGameLib.CreateTex(m_pFONT_KEY, pFontTexPath);
	}

	~Text()
	{
		std::for_each(m_pOneLineTstringVec.begin(), m_pOneLineTstringVec.end(), [](TString* pI) { delete pI; });
	}

	virtual VOID Write(const TextFormat& textFormat);

protected:
	inline VOID DivideTextByNewLine()
	{
		TString* pTString = nullptr;

		while (m_text.TextPtrPointsToEndOfText())
		{
			pTString = new TString();

			m_text.GetLine(pTString);

			m_pOneLineTstringVec.push_back(pTString);
		}
	}

	inline VOID NewCustomVerticesData(std::vector<ObjData*>* ppCharDatas, std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings) const
	{
		INT oneLineTextNum = pOneLineStrings.size();
		INT oneLineLength = NULL;
		for (INT i = 0; i < oneLineTextNum; ++i)
		{
			oneLineLength = pOneLineStrings[i]->Length();

			ppCharDatas->push_back(new ObjData[oneLineLength]);
			ppChars->push_back(new CustomVertex[CustomVertex::m_RECT_VERTICES_NUM * oneLineLength]);
		}
	}

	inline VOID ReleaseCustomVerticesData(std::vector<ObjData*>* ppCharDatas, std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings) const
	{
		INT oneLineTextNum = pOneLineStrings.size();
		INT oneLineLength = NULL;
		for (INT i = 0; i < oneLineTextNum; ++i)
		{
			oneLineLength = pOneLineStrings[i]->Length();

			delete[] (*ppCharDatas)[i];
			delete[] (*ppChars)[i];
		}
	}

	VOID CreateOneLineCharsRects(const TextFormat& textFormat, std::vector<ObjData*>* ppCharDatas, std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings) const;

	GameLib& m_rGameLib;

	const TCHAR* m_pFONT_KEY = _T("Font");

	TString m_text;
	std::vector<TString*> m_pOneLineTstringVec;
};

#endif //! TEXT_H
