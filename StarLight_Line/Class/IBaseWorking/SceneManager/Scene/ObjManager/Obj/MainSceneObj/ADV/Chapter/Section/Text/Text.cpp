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
#include "Data\TextFormat.h"
#include "Tstring\TString.h"
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

VOID Text::CreateOneLineCharsRects(const TextFormat& textFormat, std::vector<ObjData*>* ppCharDatas, std::vector<CustomVertex*>* ppChars,std::vector<TString*>& pOneLineStrings) const
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
		}
	}
}
