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
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, data);

		m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
	}
};

class StageSelectSceneStageList :public Obj
{
public:
	StageSelectSceneStageList() :Obj(OT_TRANSPARENCY, 0.9f)
	{
		Init();
	}

	~StageSelectSceneStageList()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		static BOOL isInitialized = FALSE;
		if (isInitialized) return;
		isInitialized = TRUE;

		m_rGameLib.CreateTex(_T("Icons"), _T("2DTextures/StageSelect/StageSelect_icons.png"));
	}

	inline VOID Update() 
	{
		const FLOAT ROTATE_SPEED = 1.5f;
		m_deg +=	ROTATE_SPEED * (m_deg > 0.0f) - 
					ROTATE_SPEED * (m_deg < 0.0f);

		if (m_deg != 0) return;

		m_deg = ROTATE_SPEED * m_rGameLib.KeyboardIsHeld(DIK_A) -
				ROTATE_SPEED * m_rGameLib.KeyboardIsHeld(DIK_D);
	}

	VOID Render();

private:
	struct StageIconData
	{
		ObjData m_objData;
		FLOAT m_deg;
	};

	static const INT m_STAGE_ICON_MAX = 12;
	FLOAT m_deg = 0.0f;
};

#endif // !STAGE_SELECT_SCENE_OBJ_H
