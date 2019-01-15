#include "NumText.h"

#include <windows.h>
#include <tchar.h>

VOID NumText::Write(const TextFormat& textFormat)
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

			m_rGameLib.Render(&pCustomVerticesVec[si][RECT_VERTICES_NUM * li], m_rGameLib.GetTex(_T("Nums")));
		}
	}

	ReleaseCustomVerticesData(&pCharData, &pCustomVerticesVec, m_pOneLineTstringVec);
}

VOID NumText::CreateOneLineCharsRects(const TextFormat& textFormat, std::vector<ObjData*>* ppCharDatas,
	std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings)
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

			static const FLOAT NUMS_ILLUST_SCALE = 32.0f;
			static const INT NUMS_NUM_IN_ROW = 8;
			static const INT NUMS_NUM_IN_COLUMN = 2;

			TCHAR tCharBuf[] = { '\0','\0' };
			tCharBuf[0] = m_pOneLineTstringVec[si]->GetTChar();
			INT digitNum = _ttoi(tCharBuf);

			(*ppCharDatas)[si][li].m_texUV =																						//! 統合ファイルのテクスチャの座標
			{
				NUMS_ILLUST_SCALE * ((digitNum) % NUMS_NUM_IN_ROW) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW),
				NUMS_ILLUST_SCALE * ((digitNum) / NUMS_NUM_IN_ROW) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN),
				NUMS_ILLUST_SCALE * ((digitNum) % NUMS_NUM_IN_ROW + 1) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW),
				NUMS_ILLUST_SCALE * ((digitNum) / NUMS_NUM_IN_ROW + 1) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN),
			};
		}
	}
}
