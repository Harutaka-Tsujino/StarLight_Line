#include "Result2PObj.h"

VOID ResultTwoPlayerBack::TextRender()
{
	TString resultString(_T("RESULT"));

	Text resultText(resultString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 27, 41 };

	//! RESULTの文字数の半分が3
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.5f - 2.0f * txtFormat.m_charHalfScale.m_x * 3 , 13.0f };

	resultText.Write(txtFormat);
}

VOID ResultTwoPlayerFrame::FrameRender()
{
	for (int i = 0;i < PLAYER_TYPE_MAX;++i)
	{
		ObjData data;
		data.m_center = { m_WND_SIZE.m_x * (0.25f +(0.25f * (i * 2))), m_WND_SIZE.m_y * 0.75f, m_Z };
		data.m_halfScale = { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		data.m_aRGB = D3DCOLOR_ARGB(80, 255, 255, 255);

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, data);

		m_rGameLib.Render(back, nullptr);
	}
}

VOID ResultTwoPlayerFrame::PlayerTextRender()
{
	TString OnePlayerString(_T("1P"));

	Text OnePlayerText(OnePlayerString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txt1pFormat;
	txt1pFormat.m_charHalfScale = { 30, 35 };

	txt1pFormat.m_topLeft = { m_WND_SIZE.m_x * 0.25f - txt1pFormat.m_charHalfScale.m_x * 2.0f, 200.0f };

	OnePlayerText.Write(txt1pFormat);

	TString TwoPlayerString(_T("2P"));

	Text TwoPlayerText(TwoPlayerString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txt2PFormat;
	txt2PFormat.m_charHalfScale = { 30, 35 };

	txt2PFormat.m_topLeft = { m_WND_SIZE.m_x * 0.75f - txt2PFormat.m_charHalfScale.m_x * 2.0f , 200.0f };

	TwoPlayerText.Write(txt2PFormat);
}
