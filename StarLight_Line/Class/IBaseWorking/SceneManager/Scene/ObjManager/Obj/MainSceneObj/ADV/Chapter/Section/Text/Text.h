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

#include <d3dx9.h>

#include "../../../../../../../../../../../GameLib/GameLib.h"
#include "Data/TextFormat.h"
#include "Tstring/TString.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

class Text
{
public:
	Text(const TString& text, const TCHAR* pFontTexPath) :m_rGameLib(GameLib::GetInstance())
	{
		text.WriteOutAll(&m_text);

		DivideTextByNewLine();

		if (pFontTexPath == nullptr) return;

		m_rGameLib.CreateTex(m_pFONT_KEY, pFontTexPath);
	}

	virtual ~Text()
	{
		std::for_each(m_pOneLineTstringVec.begin(), m_pOneLineTstringVec.end(), [](TString* pI) { delete pI; });
	}

	virtual VOID Write(const TextFormat& textFormat);

protected:
	Text& operator=(const Text&) = delete;
	Text(const Text&) = delete;

	inline VOID DivideTextByNewLine()
	{
		TString* pTString = nullptr;

		while (!m_text.TextPtrPointsToEndOfText())
		{
			pTString = new TString();

			m_text.GetLine(pTString);

			m_pOneLineTstringVec.push_back(pTString);
		}
	}

	inline VOID NewCustomVerticesData(std::vector<ObjData*>* ppCharDatas, std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings) const
	{
		size_t oneLineTextNum = pOneLineStrings.size();
		INT oneLineLength = NULL;
		for (INT i = 0; i < oneLineTextNum; ++i)
		{
			pOneLineStrings[i]->SeekFirst();
			oneLineLength = pOneLineStrings[i]->Length();

			ppCharDatas->push_back(new ObjData[oneLineLength]);
			ppChars->push_back(new CustomVertex[CustomVertex::m_RECT_VERTICES_NUM * oneLineLength]);
		}
	}

	inline VOID ReleaseCustomVerticesData(std::vector<ObjData*>* ppCharDatas, 
		std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings) const
	{
		size_t oneLineTextNum = pOneLineStrings.size();
		for (INT i = 0; i < oneLineTextNum; ++i)
		{
			delete[] (*ppCharDatas)[i];
			delete[] (*ppChars)[i];
		}
	}

	virtual VOID CreateOneLineCharsRects(const TextFormat& textFormat, std::vector<ObjData*>* ppCharDatas,
		std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings);

	inline VOID CutTuTvA_Z_0_9(ObjData* pObjData, TCHAR tChar)
	{
		const INT CHARS_MAX = 38;
		const TCHAR CHARS[CHARS_MAX] =
		{
			_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ")
		};
		
		INT fontNum = CHARS_MAX - 2;

		for (INT i = 0; i < CHARS_MAX - 1; ++i)
		{
			if (tChar == CHARS[i])
			{
				fontNum = i;

				break;
			}
		}

		const FLOAT ILUUST_SIZE = 2048.0f;
		const D3DXVECTOR2 FONT_SCALE = { 200.0f, 300.0f };
		const INT ONE_COLUMN_CHARS_NUM = 6;

		if (fontNum == CHARS_MAX - 2)
		{
			pObjData->m_texUV = { 0.0f, 0.0f, 0.0f, 0.0f };

			return;
		}

		pObjData->m_texUV =
		{
			FONT_SCALE.x * (fontNum % 6)	 / ILUUST_SIZE,
			FONT_SCALE.y * (fontNum / 6)	 / ILUUST_SIZE,
			FONT_SCALE.x * (fontNum % 6 + 1) / ILUUST_SIZE,
			FONT_SCALE.y * (fontNum / 6 + 1) / ILUUST_SIZE
		};
	}

	GameLib& m_rGameLib;

	const TCHAR* m_pFONT_KEY = _T("Font");

	TString m_text;
	std::vector<TString*> m_pOneLineTstringVec;
};

#endif //! TEXT_H
