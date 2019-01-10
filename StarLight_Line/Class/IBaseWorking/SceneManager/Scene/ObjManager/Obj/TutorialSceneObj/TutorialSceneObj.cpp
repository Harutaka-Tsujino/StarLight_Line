#include "TutorialSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"
#include "../../../Enum/SCENE_KIND.h"

VOID TutorialManager::Update()
{
	SceneManager& rSceneManager = SceneManager::GetInstance();

	if (m_currentConvNum == E_CONV_PLAY_END && ReturnKeyIsPressed() && !m_tutorialIsPlayed)
	{
		rSceneManager.SetNextScene(SK_RESULT);

		return;
	}

	if (m_pStarManager->GetEnds()) m_tutorialIsPlayed = FALSE;

	if (m_pTutorialSlides->Ends())
	{
		if (m_currentConvNum == E_CONV_PLAY_START && ReturnKeyIsPressed())
		{
			++m_currentConvNum;

			m_rGameLib.RestartTime();
			m_tutorialIsPlayed = TRUE;
		}

		if (m_tutorialIsPlayed) m_pStarManager->Update();

		return;
	}

	if (m_currentConvNum == E_CONV_GREETING)
	{
		if (ReturnKeyIsPressed()) ++m_currentConvNum;

		return;
	}

	if (!m_firstConvPartEnds)
	{
		if (UpKeyIsPressed())
		{
			m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

			m_yesIsSelected = !m_yesIsSelected;
		}
			
		if (DownKeyIsPressed())
		{
			m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

			m_yesIsSelected = !m_yesIsSelected;
		}

		if (ReturnKeyIsPressed())
		{
			m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

			m_firstConvPartEnds = TRUE;
		}

		return;
	}

	if (m_firstConvPartEnds)
	{
		if (m_yesIsSelected)
		{
			m_pTutorialSlides->Update();

			m_currentConvNum = E_CONV_PLAY_START;

			return;
		}

		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.SetIsTutorial(FALSE);
		rSceneManager.SetNextScene(SK_SAVE_DATA);
	}
}

VOID TutorialManager::Render()
{
	ObjData data;
	data.m_center	 = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	CustomVertex Conv[4];
	m_rGameLib.CreateRect(Conv, data);

	const TCHAR* pKey[] = { _T("Conv0"), _T("Conv1"), _T("Conv2"), _T("Conv3") };

	if (m_pTutorialSlides->Ends())
	{
		if (m_tutorialIsPlayed)
		{
			m_pStarManager->Render();

			return;
		}

		m_rGameLib.Render(Conv, m_rGameLib.GetTex(pKey[m_currentConvNum]));

		return;
	}

	if (m_firstConvPartEnds && m_yesIsSelected)
	{
		m_pTutorialSlides->Render();

		return;
	}

	m_rGameLib.Render(Conv, m_rGameLib.GetTex(pKey[m_currentConvNum]));

	if (m_currentConvNum == E_CONV_TUTORIAL_SUGGESTING)
	{
		RenderTexts();
		RenderTarget();
	}
}
