#include "MainSceneObject.h"

#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"

VOID MainBack::Init()
{
	m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/Main/main_line.png"));
}

VOID MainBack::Render()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 1.0f };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
}