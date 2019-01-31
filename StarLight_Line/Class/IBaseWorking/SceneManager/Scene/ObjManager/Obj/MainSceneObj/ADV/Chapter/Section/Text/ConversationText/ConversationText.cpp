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
	D3DXVECTOR2 fontScale = { static_cast<FLOAT>(textFormat.m_charHalfScale.m_x), static_cast<FLOAT>(textFormat.m_charHalfScale.m_y) };

	m_rGameLib.CreateFont(m_pCONV_FONT_KEY, fontScale, _T("遊ゴシック"), 0);

	CountUp();

	INT convTextCatForStagingLength = m_currentTextLength + 1;

	if (convTextCatForStagingLength <= 1) return;

	TCHAR* pConvTextCatForStaging = new TCHAR[convTextCatForStagingLength];

	ZeroMemory(pConvTextCatForStaging, sizeof(TCHAR)* convTextCatForStagingLength);

	_tcsncpy_s(pConvTextCatForStaging, convTextCatForStagingLength, m_pConvText, _TRUNCATE);

	m_rGameLib.Render(textFormat.m_topLeft, pConvTextCatForStaging, DT_LEFT, m_rGameLib.GetFont(m_pCONV_FONT_KEY));

	delete[] pConvTextCatForStaging;

	m_rGameLib.EraseFont(m_pCONV_FONT_KEY);
}
