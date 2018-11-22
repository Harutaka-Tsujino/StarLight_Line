#ifndef STAGE_SELECT_SCENE_OBJ_H
#define STAGE_SELECT_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"

class StageSelectBack :public Obj
{
public:
	StageSelectBack() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~StageSelectBack()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		static BOOL isInitialized = FALSE;
		if (isInitialized) return;
		isInitialized = TRUE;

		m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/Title/title_background.png"));
	}

	inline VOID Update() {};

	inline VOID Render()
	{
		m_rGameLib.SetCameraTransform();

		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 1.0f };
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, data);

		m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
	}
};

#endif // !STAGE_SELECT_SCENE_OBJ_H
