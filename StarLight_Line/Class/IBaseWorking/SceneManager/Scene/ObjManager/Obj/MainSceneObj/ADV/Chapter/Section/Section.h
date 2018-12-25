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

#include "Text\Data\TextFormat.h"
#include "Text\Tstring\TString.h"
#include "Text\ConversationText\ConversationText.h"

class Section :public Obj
{
public:
	explicit Section(const TString& sectionText) :Obj(OT_TRANSPARENCY, 0.0f)
	{
		DevideTextsByConversationAndSet(sectionText);
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
	}

	inline VOID Update()
	{
		if (!ReturnKeyIsPressed()) return;

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
		speakerFormat.m_topLeft = { m_WND_SIZE.m_x * 0.01f, m_WND_SIZE.m_y * 0.5f };
		speakerFormat.m_charHalfScale = { 7, 14 };

		TextFormat textFormat;
		textFormat.m_topLeft = { m_WND_SIZE.m_x * 0.01f, m_WND_SIZE.m_y * 0.6f };
		textFormat.m_charHalfScale = { 10, 20 };

		m_pConversationTexts[m_currentConversationTextElementNum]->Write(speakerFormat, textFormat);
	}

	inline BOOL Ends() const
	{
		return m_ends;
	}

private:
	struct ConversationTString
	{
	public:
		TString m_speaker;
		TString m_conversation;
	};

	Section& operator=(const Section&) = delete;
	Section(const Section&) = delete;

	inline VOID TransEndedTextNextText()
	{
		if (m_currentConversationTextElementNum == m_pConversationTexts.size() - 1)
		{
			m_ends = TRUE;

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

	INT m_currentConversationTextElementNum = 0;

	BOOL m_ends = FALSE;

	static const TCHAR m_NAME_TAG = '@';
	
	std::vector<ConversationTString*> m_pConversationTStrings;

	const TCHAR* m_pFONT_TEX_PATH = _T("現在画像なし");

	std::vector<ConversationText*> m_pConversationTexts;
};

#endif //! SECTION_H
