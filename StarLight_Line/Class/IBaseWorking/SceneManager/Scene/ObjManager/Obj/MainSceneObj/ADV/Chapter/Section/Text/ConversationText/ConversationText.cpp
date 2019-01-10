/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#include "ConversationText.h"

#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "../Text.h"
#include "../../../../../../../../../../../../GameLib/GameLib.h"
#include "../Data/TextFormat.h"
#include "../Tstring/TString.h"
#include "../../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

VOID ConversationText::Write(const TextFormat& textFormat)
{
	CountUp();

	std::vector<ObjData*> pCharData;
	std::vector<CustomVertex*> pCustomVerticesVec;

	NewCustomVerticesData(&pCharData, &pCustomVerticesVec, m_pOneLineTstringVec);

	CreateOneLineCharsRects(textFormat, &pCharData, &pCustomVerticesVec, m_pOneLineTstringVec);

	INT oneLineLength = NULL;

	const INT RECT_VERTICES_NUM = CustomVertex::m_RECT_VERTICES_NUM;

	INT charRectsNum = 0;

	for (INT si = 0; si < m_pOneLineTstringVec.size(); ++si)
	{
		oneLineLength = m_pOneLineTstringVec[si]->Length();

		if (charRectsNum > m_currentCharRectsMax) break;

		for (INT li = 0; li < oneLineLength; ++li)
		{
			m_rGameLib.CreateRect(&pCustomVerticesVec[si][RECT_VERTICES_NUM * li], pCharData[si][li]);

			m_rGameLib.Render(&pCustomVerticesVec[si][RECT_VERTICES_NUM * li], m_rGameLib.GetTex(m_pFONT_KEY));

			++charRectsNum;
		}
	}

	ReleaseCustomVerticesData(&pCharData, &pCustomVerticesVec, m_pOneLineTstringVec);
}
