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

#include "../../../../../../../../../../../GameLib/GameLib.h"
#include "Data\TextFormat.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

class Text
{
public:
	Text(const TCHAR* pText, const TCHAR* pFontTexPath) :m_rGameLib(GameLib::GetInstance()), m_pText(pText)
	{
		const TCHAR* pFONT_KEY = _T("Font");

		if (m_rGameLib.TexExists(pFONT_KEY)) return;

		m_rGameLib.CreateTex(pFONT_KEY, pFontTexPath);
	}

	VOID Write(const TextFormat& textFormat)
	{
		size_t charsNum = _tcslen(m_pText);

		ObjData* pCharData = new ObjData[charsNum];

		INT newLinesNum = 0;

		FLOAT halfX = static_cast<FLOAT>(textFormat.m_charHalfScale.m_x);
		FLOAT halfY = static_cast<FLOAT>(textFormat.m_charHalfScale.m_y);

		INT oneLineStrLen = 0;

		std::vector<TCHAR*> m_pOneLineTcharsVec;

		for (INT i = 0;; ++i)
		{
			/*m_pOneLineTcharsVec.push_back((m_pText))

			m_oneLineTcharsVecVec
*/
		}


		for (INT i = 0; i < charsNum; ++i)
		{
			//if () oneLineStrLen;

			pCharData[i].m_center = 
			{ 
				textFormat.m_topLeft.x + halfX + oneLineStrLen * (halfX * 2 + textFormat.m_charGap.x),
				textFormat.m_topLeft.y + halfY + newLinesNum * (halfY * 2 + textFormat.m_charGap.y),
				0.0f 
			};

			textFormat.m_charHalfScale.TransD3DXVECTOR3(&pCharData[i].m_halfScale);

			
		}
	}

private:
	const TCHAR* GetTokNext(const TCHAR* pString, TCHAR delimiter)
	{
		size_t prevTokElementnum = 0;
		for (INT i = 0; pString[i] != delimiter || pString[i] != delimiter; ++i)
		{
			++prevTokElementnum;
		}

		return &pString[prevTokElementnum + 2];
	}

	//const size_t GetLengthToNewLine()

	GameLib& m_rGameLib;

	const TCHAR* m_pText = nullptr;
};

#endif //! TEXT_H
