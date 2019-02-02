/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef SECTION_H
#define SECTION_H

#include <windows.h>
#include <tchar.h>

#include <vector>

#include "../../../../Enum/OBJ_TYPE.h"
#include "../../../../Obj.h"

#include "Text/Data/TextFormat.h"
#include "Text/Tstring/TString.h"
#include "Text/ConversationText/ConversationText.h"

class Section :public Obj
{
public:
	explicit Section(const TString& sectionText) :Obj(OT_TRANSPARENCY, 0.0f)
	{
		DevideTextsByConversationAndSet(sectionText);

		m_zodiacSignsObjData.m_center	 = { m_WND_SIZE.m_x * 0.5f, -m_ZODIAC_SIGNS_POS_Y, 0.0f };
		m_zodiacSignsObjData.m_halfScale = { m_WND_SIZE.m_x * 0.4f,  m_WND_SIZE.m_y * 0.4f, 0.0f };

		m_rGameLib.CreateTex(m_pZODIAC_ICON_TEX_KEY, GetTexPath());
	}

	~Section()
	{
		for (auto i : m_pConversationTexts)
		{
			delete i;
		}

		for (auto i : m_pConversationTStrings)
		{
			delete i;
		}

		m_rGameLib.EraseTex(m_pZODIAC_ICON_TEX_KEY);
	}

	inline VOID Update()
	{
		if (m_part == PART_ZODIAC_APPEARANCE)
		{
			MakeZodiacAppear(FALSE);
		}

		if (m_part == PART_ZODIAC_LEAVING)
		{
			MakeZodiacDisappear(FALSE);
		}

		if (!ReturnKeyIsPressed()) return;

		//if (m_part == PART_ZODIAC_APPEARANCE)
		//{
		//	MakeZodiacAppear(TRUE);
		//}

		//if (m_part == PART_ZODIAC_LEAVING)
		//{
		//	MakeZodiacDisappear(TRUE);
		//}

		if (m_part != PART_CONVERSATION)
		{
			return;
		}

		if (m_pConversationTexts[m_currentConversationTextElementNum]->StagingEnds())
		{
			TransEndedTextNextText();

			return;
		}

		m_pConversationTexts[m_currentConversationTextElementNum]->SkipStaging();
	}

	inline VOID Render()
	{
		TextFormat speakerFormat;
		speakerFormat.m_topLeft = { m_WND_SIZE.m_x * 0.13f, m_WND_SIZE.m_y * 0.695f };
		speakerFormat.m_charHalfScale.m_y = 2 * (speakerFormat.m_charHalfScale.m_x = 14);

		TextFormat textFormat;
		textFormat.m_topLeft = { m_WND_SIZE.m_x * 0.12f, m_WND_SIZE.m_y * 0.78f };
		textFormat.m_charHalfScale.m_y = 2 * (textFormat.m_charHalfScale.m_x = 12);

		RenderZodiacSigns();
		
		if (m_part != PART_CONVERSATION)
		{
			return;
		}

		m_pConversationTexts[m_currentConversationTextElementNum]->Write(speakerFormat, textFormat);
	}

	inline BOOL Ends() const
	{
		return m_ends;
	}

private:
	enum PART
	{
		PART_ZODIAC_APPEARANCE,
		PART_CONVERSATION,
		PART_ZODIAC_LEAVING,
	};

	struct ConversationTString
	{
	public:
		TString m_speaker;
		TString m_conversation;
	};

	Section& operator=(const Section&) = delete;
	Section(const Section&) = delete;

	inline VOID MakeZodiacAppear(BOOL isMoment)
	{
		if (isMoment)
		{
			m_zodiacSignsObjData.m_center.y = m_ZODIAC_SIGNS_POS_Y;
		}

		m_zodiacSignsObjData.m_center.y += 2.0f * m_ZODIAC_SIGNS_POS_Y / m_ZODIAC_STAGING_FRAME_COUNT;

		if (m_zodiacSignsObjData.m_center.y < m_ZODIAC_SIGNS_POS_Y)
		{
			return;
		}

		m_zodiacSignsObjData.m_center.y = m_ZODIAC_SIGNS_POS_Y;

		m_part = PART_CONVERSATION;
	}

	inline VOID MakeZodiacDisappear(BOOL isMoment)
	{
		if (isMoment)
		{
			m_zodiacSignsObjData.m_center.y = -m_ZODIAC_SIGNS_POS_Y;
		}

		m_zodiacSignsObjData.m_center.y -= 2.0f * m_ZODIAC_SIGNS_POS_Y / m_ZODIAC_STAGING_FRAME_COUNT;

		if (m_zodiacSignsObjData.m_center.y > -m_ZODIAC_SIGNS_POS_Y)
		{
			return;
		}

		m_zodiacSignsObjData.m_center.y = -m_ZODIAC_SIGNS_POS_Y;

		m_ends = TRUE;
	}

	inline VOID RenderZodiacSigns()
	{
		m_rGameLib.CreateAndRenderRect(m_zodiacSignsObjData, m_rGameLib.GetTex(m_pZODIAC_ICON_TEX_KEY));
	}

	inline VOID TransEndedTextNextText()
	{
		if (m_currentConversationTextElementNum == m_pConversationTexts.size() - 1)
		{
			m_part = PART_ZODIAC_LEAVING;

			return;
		}

		if (!m_pConversationTexts[m_currentConversationTextElementNum]->StagingEnds()) return;

		++m_currentConversationTextElementNum;
	}

	inline VOID DiscriminateSpeakerAndSet(TString* pTextForConversion, ConversationTString* pConversationBuf) const
	{
		TCHAR tCharBuf = NULL;

		if (pTextForConversion->GetTChar() != m_NAME_TAG) return;

		while (tCharBuf = pTextForConversion->GetTChar())
		{
			if (tCharBuf == m_NAME_TAG) break;

			pConversationBuf->m_speaker.WriteInChar(tCharBuf);
		}

		pConversationBuf->m_speaker.WriteInChar(TString::m_TEXT_END);

		pTextForConversion->Shift(TString::m_NEW_LINE_AND_RETURN_LENGTH);
	}

	inline VOID DiscriminateConversationAndSet(TString* pTextForConversion, ConversationTString* pConversationBuf) const
	{
		TCHAR tCharBuf = NULL;

		while ((tCharBuf = pTextForConversion->GetTChar()) != TString::m_TEXT_END)
		{
			if (tCharBuf == m_NAME_TAG)
			{
				pTextForConversion->Shift(-1);	//! ネームタグを呼んでしまったのでテキストポインタをネームタグまで戻す

				break;
			}

			pConversationBuf->m_conversation.WriteInChar(tCharBuf);
		}

		pConversationBuf->m_conversation.WriteInChar(TString::m_TEXT_END);
	}

	VOID DevideTextsByConversationAndSet(const TString& sectionText);

	const TCHAR* GetTexPath();

	PART m_part = PART_ZODIAC_APPEARANCE;

	const FLOAT m_ZODIAC_SIGNS_POS_Y = 280.0f;
	const INT m_ZODIAC_STAGING_FRAME_COUNT = 120;

	ObjData m_zodiacSignsObjData;

	INT m_currentConversationTextElementNum = 0;

	BOOL m_ends = FALSE;

	static const TCHAR m_NAME_TAG = '@';
	
	std::vector<ConversationTString*> m_pConversationTStrings;

	const TCHAR* m_pZODIAC_ICON_TEX_KEY = _T("ZodiacSigns");

	std::vector<ConversationText*> m_pConversationTexts;
};

#endif //! SECTION_H
