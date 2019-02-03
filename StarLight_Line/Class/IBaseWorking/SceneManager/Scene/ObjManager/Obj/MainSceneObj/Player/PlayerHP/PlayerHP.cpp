#include "PlayerHP.h"

#include "../../../../../../SceneManager.h"

VOID PlayerHP::Init()
{
	m_HP = 5;
	m_rGameLib.CreateTex(_T("HP"), _T("2DTextures/Main/main_life.png"));
}

VOID PlayerHP::Update()
{
	m_invincibleCount = (m_isInvincible) ? ++m_invincibleCount : 0;

	const INT INVINCIBLE_COUNT_MAX = 120;

	if (m_invincibleCount > INVINCIBLE_COUNT_MAX)
	{
		m_isInvincible = FALSE;
	}

	if (m_changeDefaultFlashFrameCount >= 0)
	{
		++m_changeDefaultFlashFrameCount;
	}

	/*if (0 < m_changeDefaultFlashFrameCount && m_changeDefaultFlashFrameCount <= INVINCIBLE_COUNT_MAX)
	{
		const INT FLASH_PERIOD_COUNT = 8;

		m_AdditionalFlashMulti = ((m_changeDefaultFlashFrameCount % FLASH_PERIOD_COUNT) / (FLASH_PERIOD_COUNT / 2)) ? -1 : 0;
	}*/

	if (m_changeDefaultFlashFrameCount > INVINCIBLE_COUNT_MAX)
	{
		m_AdditionalFlashMulti = 0;

		m_changeDefaultFlashFrameCount = m_DO_NOTHING_FRAME_COUNT_NUM;
	}

	if (m_isInvincible) return;

	const INT HIT_MODE = 1;

	if (m_rGameCollision.HitSomething(_T("Player"), DAMAGE, HIT_MODE))
	{
		m_isInvincible = TRUE;

		m_AdditionalFlashMulti = -1;

		m_changeDefaultFlashFrameCount = 0;

		CreateVertex();

		if (m_HP <= 0)
		{
			SceneManager& rSceneManager = SceneManager::GetInstance();

			rSceneManager.TurnOffBGM();

			m_rGameLib.SetVolume(_T("HitLethal"), 100);
			m_rGameLib.OneShotSimultaneousSound(_T("HitLethal"));

			return;
		}

		--m_HP;

		m_rGameLib.OneShotSimultaneousSound(_T("HitWhite"));
	}
}

VOID PlayerHP::Render()
{
	//static INT flashCnt[5];

	for (int i = 0;i != m_HpRect.size();++i)
	{
		ObjData Data;
		Data.m_center	 = { m_WND_SIZE.m_x * (0.38f - 0.082f*i), m_WND_SIZE.m_y * 0.9f, 0.0f };
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.0395f, m_WND_SIZE.m_y * 0.032f, 0.0f };
		CutUV(&Data.m_texUV);

		m_rGameLib.CreateRect(m_HpRect[i], Data);

		//m_rGameLib.FlashRect(m_HpRect[i], &flashCnt[i], 60, 250, 190);

		m_rGameLib.Render(m_HpRect[i], m_rGameLib.GetTex(_T("HP")));
	}
}

VOID PlayerHP::CutUV(TexUV* UV)
{
	UV->m_startTV = 74.f / 512.f;
	UV->m_endTU	  = 80.f / 512.f;
	UV->m_endTV	  = 124.f / 512.f;
}

VOID PlayerHP::CreateVertex()
{
	m_HpRect.push_back(new CustomVertex[4]);
}

VOID PlayerHP::ReleaseVertex()
{
	for (int i = 0;i != m_HpRect.size();++i)
	{
		delete[] m_HpRect[i];
		m_HpRect[i] = nullptr;
	}
}
