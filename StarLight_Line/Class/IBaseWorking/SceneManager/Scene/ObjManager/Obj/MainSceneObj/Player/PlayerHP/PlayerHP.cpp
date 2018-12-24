#include "PlayerHP.h"

VOID PlayerHP::Init()
{
	m_HP = 5;
	m_rGameLib.CreateTex(_T("HP"), _T("2DTextures/Main/main_life.png"));
}

VOID PlayerHP::Update()
{
	if (m_HP <= 0)
	{
		return;
	}

	const FLOAT PLAYER_RADIUS = 20.f;
	const FLOAT ENEMY_RADIUS  = 20.f;

	if (m_rGameCollision.HitSomething(_T("Player"), DAMAGE, PLAYER_RADIUS, ENEMY_RADIUS))
	{
		CreateVertex();

		--m_HP;

		if (m_HP <= 0)
		{
			m_rGameLib.OneShotSimultaneousSound(_T("HitLethal"));

			return;
		}

		m_rGameLib.OneShotSimultaneousSound(_T("HitWhite"));
	}
}

VOID PlayerHP::Render()
{
	for (int i = 0;i != m_HpRect.size();++i)
	{
		ObjData Data;
		Data.m_center = { m_WND_SIZE.m_x * (0.38f - 0.082f*i), m_WND_SIZE.m_y * 0.9f, 0.0f };
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.0395f, m_WND_SIZE.m_y * 0.032f, 0.0f };
		CutUV(&Data.m_texUV);

		m_rGameLib.CreateRect(m_HpRect[i], Data);

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
