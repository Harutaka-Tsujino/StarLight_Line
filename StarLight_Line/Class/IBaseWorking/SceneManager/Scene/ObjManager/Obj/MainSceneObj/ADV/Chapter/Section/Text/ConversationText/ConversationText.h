/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef CONVERSATION_TEXT_H
#define CONVERSATION_TEXT_H

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

class ConversationText :public Text
{
public:
	ConversationText(const TString& speaker, const TString& text, const TCHAR* pFontTexPath) :Text(text, nullptr)
	{
		m_pSpeaker = new TCHAR[speaker.Size()];
		speaker.WriteOutAll(m_pSpeaker);

		m_pConvText = new TCHAR[text.Size()];
		text.WriteOutAll(m_pConvText);

		m_textSize = static_cast<INT>(text.Size());

		m_rGameLib.CreateTex(m_pADV_BACK_TEX_KEY, _T("2DTextures/Main/adv_textframe.png"));
	}

	~ConversationText()
	{
		m_rGameLib.EraseTex(m_pADV_BACK_TEX_KEY);
		delete[] m_pConvText;
		delete[] m_pSpeaker;
	}

	inline VOID Write(const TextFormat& speakerNameFormat, const TextFormat& textFormat)
	{
		RenderBack();

		WriteSpeaker(speakerNameFormat);

		Write(textFormat);
	}

	inline VOID SkipStaging()
	{
		m_currentTextLength = m_textSize;
	}

	inline BOOL StagingEnds() const
	{
		return m_stagingEnds;
	}

private:
	inline VOID RenderBack()
	{
		RectSize m_wndSize = m_rGameLib.GetWndSize();

		ObjData rectData;
		rectData.m_center	 = { m_wndSize.m_x * 0.5f, m_wndSize.m_y *0.83f, 0.0f };
		rectData.m_halfScale = { m_wndSize.m_x * 0.4f, m_wndSize.m_y *0.17f, 0.0f };

		m_rGameLib.CreateAndRenderRect(rectData, m_rGameLib.GetTex(m_pADV_BACK_TEX_KEY));
	}

	VOID Write(const TextFormat& textFormat);

	inline VOID WriteSpeaker(const TextFormat& speakerNameFormat) const
	{
		D3DXVECTOR2 fontScale = { static_cast<FLOAT>(speakerNameFormat.m_charHalfScale.m_x), static_cast<FLOAT>(speakerNameFormat.m_charHalfScale.m_y) };

		m_rGameLib.CreateFont(m_pSPEAKER_FONT_KEY, fontScale, _T("遊ゴシック"), 0);

		m_rGameLib.Render(speakerNameFormat.m_topLeft, m_pSpeaker, DT_LEFT, m_rGameLib.GetFont(m_pSPEAKER_FONT_KEY));

		m_rGameLib.EraseFont(m_pSPEAKER_FONT_KEY);
	}

	inline VOID CountUp()
	{
		const INT ONE_CHAR_STAGING_FRAME = 6;

		++m_oneCharStagingFrameCount;

		if (m_oneCharStagingFrameCount < ONE_CHAR_STAGING_FRAME) return;

		++m_currentTextLength;

		m_oneCharStagingFrameCount = 0;

		if (m_currentTextLength < m_textSize) return;

		m_currentTextLength = m_textSize;

		m_stagingEnds = TRUE;
	}

	ConversationText(const ConversationText &other) = delete;
	ConversationText &operator=(const ConversationText &other) = delete;

	const TCHAR* m_pADV_BACK_TEX_KEY = _T("ADVBack");

	const TCHAR* m_pSPEAKER_FONT_KEY = _T("SpeakerFont");
	const TCHAR* m_pCONV_FONT_KEY = _T("ConvFont");

	TCHAR* m_pSpeaker = nullptr;
	TCHAR* m_pConvText = nullptr;

	INT m_currentTextLength = 0;
	INT m_oneCharStagingFrameCount = 0;

	INT m_textSize = 0;

	BOOL m_stagingEnds = FALSE;
};

#endif //! CONVERSATION_TEXT_H
