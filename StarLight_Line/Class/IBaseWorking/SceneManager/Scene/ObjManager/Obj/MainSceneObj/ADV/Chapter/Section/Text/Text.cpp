/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#include "Text.h"

#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "../../../../../../../../../../../GameLib/GameLib.h"
#include "Data/TextFormat.h"
#include "Tstring/TString.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

VOID Text::Write(const TextFormat& textFormat)
{
	std::vector<ObjData*> pCharData;
	std::vector<CustomVertex*> pCustomVerticesVec;

	NewCustomVerticesData(&pCharData, &pCustomVerticesVec, m_pOneLineTstringVec);

	CreateOneLineCharsRects(textFormat, &pCharData, &pCustomVerticesVec, m_pOneLineTstringVec);

	INT oneLineLength = NULL;

	const INT RECT_VERTICES_NUM = CustomVertex::m_RECT_VERTICES_NUM;

	for (INT si = 0; si < m_pOneLineTstringVec.size(); ++si)
	{
		oneLineLength = m_pOneLineTstringVec[si]->Length();

		for (INT li = 0; li < oneLineLength; ++li)
		{
			m_rGameLib.CreateRect(&pCustomVerticesVec[si][RECT_VERTICES_NUM * li], pCharData[si][li]);

			m_rGameLib.Render(&pCustomVerticesVec[si][RECT_VERTICES_NUM * li], m_rGameLib.GetTex(m_pFONT_KEY));
		}
	}

	ReleaseCustomVerticesData(&pCharData, &pCustomVerticesVec, m_pOneLineTstringVec);
}

VOID Text::CreateOneLineCharsRects(const TextFormat& textFormat, std::vector<ObjData*>* ppCharDatas, 
	std::vector<CustomVertex*>* ppChars,std::vector<TString*>& pOneLineStrings)
{
	INT oneLineLength = NULL;

	FLOAT halfX = static_cast<FLOAT>(textFormat.m_charHalfScale.m_x);
	FLOAT halfY = static_cast<FLOAT>(textFormat.m_charHalfScale.m_y);

	const INT RECT_VERTICES_NUM = CustomVertex::m_RECT_VERTICES_NUM;

	for (INT si = 0; si < m_pOneLineTstringVec.size(); ++si)
	{
		oneLineLength = m_pOneLineTstringVec[si]->Length();

		for (INT li = 0; li < oneLineLength; ++li)
		{
			(*ppCharDatas)[si][li].m_center =
			{
				textFormat.m_topLeft.x + halfX + li * (2 * halfX + textFormat.m_charGap.x),
				textFormat.m_topLeft.y + halfY + si * (2 * halfY + textFormat.m_charGap.y),
				0.0f
			};

			textFormat.m_charHalfScale.TransD3DXVECTOR3(&(*ppCharDatas)[si][li].m_halfScale);

			CutTuTvA_Z_0_9(&(*ppCharDatas)[si][li], m_pOneLineTstringVec[si]->GetTChar(li));

			(*ppCharDatas)[si][li].m_aRGB = textFormat.m_color;
		}
	}
}

VOID Text::CutTuTvA_Z_0_9(ObjData* pObjData, TCHAR tChar)
{
	const INT CHARS_MAX = 40;
	const TCHAR CHARS[CHARS_MAX] =
	{
		_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:/ ")
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

	const INT NOT_NUMBER = 36;

	if (fontNum >= NOT_NUMBER)
	{
		pObjData->m_texUV =
		{
			FONT_SCALE.x * (6 + fontNum - NOT_NUMBER) / ILUUST_SIZE,
			0.0f									  / ILUUST_SIZE,
			FONT_SCALE.x * (7 + fontNum - NOT_NUMBER) / ILUUST_SIZE,
			FONT_SCALE.y							  / ILUUST_SIZE
		};

		return;
	}

	pObjData->m_texUV =
	{
		FONT_SCALE.x * (fontNum % 6) / ILUUST_SIZE,
		FONT_SCALE.y * (fontNum / 6) / ILUUST_SIZE,
		FONT_SCALE.x * (fontNum % 6 + 1) / ILUUST_SIZE,
		FONT_SCALE.y * (fontNum / 6 + 1) / ILUUST_SIZE
	};
}
