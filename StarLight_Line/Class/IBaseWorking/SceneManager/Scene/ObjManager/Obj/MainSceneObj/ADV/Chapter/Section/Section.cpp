/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#include "Section.h"

#include <windows.h>
#include <tchar.h>

#include <vector>

#include "../../../../Enum/OBJ_TYPE.h"
#include "../../../../Obj.h"

#include "Text/Data/TextFormat.h"
#include "Text/Tstring/TString.h"
#include "Text/ConversationText/ConversationText.h"

VOID Section::DevideTextsByConversationAndSet(const TString& sectionText)
{
	TString textForConversion;

	sectionText.WriteOutAll(&textForConversion);

	ConversationTString* pConversationBuf = nullptr;

	ConversationText* pConversationText = nullptr;

	for (INT i = 0; !textForConversion.TextPtrPointsToEndOfText(); ++i)
	{
		pConversationBuf = new ConversationTString;

		DiscriminateSpeakerAndSet(&textForConversion, pConversationBuf);
		DiscriminateConversationAndSet(&textForConversion, pConversationBuf);

		m_pConversationTStrings.push_back(pConversationBuf);

		pConversationText = new ConversationText(	m_pConversationTStrings[i]->m_speaker,
													m_pConversationTStrings[i]->m_conversation,
													m_pFONT_TEX_PATH);

		m_pConversationTexts.push_back(pConversationText);
	}
}
