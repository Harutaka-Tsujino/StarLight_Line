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
#include "../../../../../../../SceneManager.h"

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
													m_pZODIAC_ICON_TEX_KEY);

		m_pConversationTexts.push_back(pConversationText);
	}
}

const TCHAR* Section::GetTexPath()
{
	StageData stageData;
	SceneManager::GetInstance().GetStageData(&stageData);

	switch (stageData.m_stage)
	{
	case STAGE_TAURUS:
		return _T("StageData/Chapter/adv_icon01.png");

	case STAGE_LIBRA:
		return _T("StageData/Chapter/adv_icon02.png");

	case STAGE_VIRGO:
		return _T("StageData/Chapter/adv_icon03.png");

	case STAGE_ARIES:
		return _T("StageData/Chapter/adv_icon04.png");

	case STAGE_GEMINI:
		return _T("StageData/Chapter/adv_icon05.png");

	case STAGE_SCORPIUS:
		return _T("StageData/Chapter/adv_icon06.png");

	case STAGE_PISCORPIUS:
		return _T("StageData/Chapter/adv_icon07.png");

	case STAGE_LEO:
		return _T("StageData/Chapter/adv_icon08.png");

	case STAGE_CAPRICORNUS:
		return _T("StageData/Chapter/adv_icon09.png");

	case STAGE_AQUARIUS:
		return _T("StageData/Chapter/adv_icon10.png");

	case STAGE_SAGITTARIUS:
		return _T("StageData/Chapter/adv_icon11.png");

	case STAGE_CANCER:
		return _T("StageData/Chapter/adv_icon12.png");

	case STAGE_BLACK_HOLE:
		return _T("StageData/Chapter/adv_icon13.png");
	}

	return nullptr;
}
