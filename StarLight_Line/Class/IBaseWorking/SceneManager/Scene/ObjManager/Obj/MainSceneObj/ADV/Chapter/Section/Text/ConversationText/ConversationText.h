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
	ConversationText(const TString& speaker, const TString& text, const TCHAR* pFontTexPath) :Text(text, pFontTexPath)
	{
		speaker.WriteOutAll(&m_speaker);

		for (auto i : m_pOneLineTstringVec)
		{
			m_charRectsMax += i->Length();
		}
	}

	inline VOID Write(const TextFormat& speakerNameFormat, const TextFormat& textFormat)
	{
		WriteSpeaker(speakerNameFormat);

		Write(textFormat);
	}

	VOID Write(const TextFormat& textFormat);

	inline VOID SkipStaging()
	{
		m_currentCharRectsMax = m_charRectsMax;
	}

	inline BOOL StagingEnds() const
	{
		return m_stagingEnds;
	}

private:
	inline VOID WriteSpeaker(const TextFormat& speakerNameFormat) const
	{
		ObjData speakerData;
		CustomVertex speaker[CustomVertex::m_RECT_VERTICES_NUM];

		speakerData.m_center =
		{
			speakerNameFormat.m_topLeft.x + speakerNameFormat.m_charHalfScale.m_x,
			speakerNameFormat.m_topLeft.y + speakerNameFormat.m_charHalfScale.m_y,
			0.0f
		};

		speakerNameFormat.m_charHalfScale.TransD3DXVECTOR3(&speakerData.m_halfScale);

		m_rGameLib.CreateRect(speaker, speakerData);

		m_rGameLib.Render(speaker, m_rGameLib.GetTex(m_pFONT_KEY));
	}

	inline VOID CountUp()
	{
		const INT ONE_CHAR_STAGING_FRAME = 10;

		++m_oneCharStagingFrameCount;

		if (m_oneCharStagingFrameCount < ONE_CHAR_STAGING_FRAME) return;

		++m_currentCharRectsMax;

		m_oneCharStagingFrameCount = 0;

		if (m_currentCharRectsMax < m_charRectsMax) return;

		m_currentCharRectsMax = m_charRectsMax;

		m_stagingEnds = TRUE;
	}

	ConversationText(const ConversationText &other) = delete;
	ConversationText &operator=(const ConversationText &other) = delete;

	TString m_speaker;

	INT m_currentCharRectsMax = 0; 

	INT m_oneCharStagingFrameCount = 0;

	INT m_charRectsMax = 0;

	BOOL m_stagingEnds = FALSE;
};

#endif //! CONVERSATION_TEXT_H
