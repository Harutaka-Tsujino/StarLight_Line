#include "MainSceneObject.h"

#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"

VOID MainBack::Init()
{
	m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/Main/main_back01.png"));
}

VOID MainBack::Render()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
}

VOID MainLine::Init()
{
	m_rGameLib.CreateTex(_T("Line"), _T("2DTextures/Main/main_line.png"));
}

VOID MainLine::Render()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Line")));
}

VOID PlayerLifeFrame::Init()
{
	m_rGameLib.CreateTex(_T("HpMax"), _T("2DTextures/Main/main_life.png"));
}

VOID PlayerLifeFrame::Render()
{
	m_rGameLib.SetCameraTransform();

	D3DXVECTOR3 Center, HalfScale;
	Center		= { m_WND_SIZE.m_x * 0.25f, m_WND_SIZE.m_y * 0.9f, m_Z };
	HalfScale	= { m_WND_SIZE.m_x * 0.25f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	TexUV UV;
	UV.m_endTV = 74.f / 512.f;

	CustomVertex PlayerLifeBack[4];
	m_rGameLib.CreateRect(PlayerLifeBack, Center, HalfScale,
		0xFFFFFFFF, UV.m_startTU, UV.m_startTV, UV.m_endTU, UV.m_endTV);

	m_rGameLib.Render(PlayerLifeBack, m_rGameLib.GetTex(_T("HpMax")));
}

VOID PlayerScoreFrame::Init()
{
	m_rGameLib.CreateTex(_T("ScoreFrame"), _T("2DTextures/Main/main_scoreframe.png"));
}

VOID PlayerScoreFrame::Render()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center = { m_WND_SIZE.m_x * 0.8f, m_WND_SIZE.m_y * 0.9f, 0.005f };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.18f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("ScoreFrame")));
}

VOID PlayerClearStarObj::Init()
{
	m_rGameLib.CreateTex(_T("ClearStarFrame"),_T("2DTextures/Main/main_sterframe.png"));
	m_rGameLib.CreateTex(_T("ClearStar"), _T("2DTextures/Main/Main_ClearStar.png"));
}

VOID PlayerClearStarObj::Render()
{
	RenderFrame();
	RenderStarObtained();
}

VOID PlayerClearStarObj::RenderFrame()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center		= { m_WND_SIZE.m_x * 0.53f, m_WND_SIZE.m_y * 0.9f, 0.005f };
	data.m_halfScale	= { m_WND_SIZE.m_x * 0.07f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("ClearStarFrame")));
}

VOID PlayerClearStarObj::RenderStarObtained()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center = { m_WND_SIZE.m_x * 0.487f, m_WND_SIZE.m_y * 0.9f, 0.004f };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.017f, m_WND_SIZE.m_y * 0.027f, 0.0f };
	data.m_aRGB = 0xFF98FB98;

	CustomVertex StarImage[4];
	m_rGameLib.CreateRect(StarImage, data);

	m_rGameLib.Render(StarImage, m_rGameLib.GetTex(_T("ClearStar")));
}
