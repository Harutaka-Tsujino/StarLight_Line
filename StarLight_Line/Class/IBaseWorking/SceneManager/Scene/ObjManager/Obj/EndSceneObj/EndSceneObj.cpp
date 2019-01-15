/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#include "EndSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"

VOID EndSceneEiwi::Render()
{
	ObjData data;
	data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	static INT frameCount = 0;

	static INT fadeInCount = 0;
	const INT FADE_IN_COUNT_MAX = 220;
	const INT FRAME_COUNT_MAX = FADE_IN_COUNT_MAX + 30;

	fadeInCount = (frameCount >= FADE_IN_COUNT_MAX) ? FADE_IN_COUNT_MAX : ++fadeInCount;
	data.m_aRGB = D3DCOLOR_ARGB(static_cast<BYTE>(255 * fadeInCount / FADE_IN_COUNT_MAX), 255, 255, 255);

	CustomVertex eiwi[4];
	m_rGameLib.CreateRect(eiwi, data);

	m_rGameLib.Render(eiwi, m_rGameLib.GetTex(_T("Eiwi")));

	if (++frameCount >= FRAME_COUNT_MAX) PostQuitMessage(0);
}
