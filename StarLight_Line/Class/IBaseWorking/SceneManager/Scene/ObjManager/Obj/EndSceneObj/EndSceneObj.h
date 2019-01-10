/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#ifndef END_SCENE_OBJ_H
#define END_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"

class EndSceneBack :public Obj
{
public:
	EndSceneBack() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~EndSceneBack()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/SaveData/SaveData_Back.jpg"));
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

class EndSceneEiwi :public Obj
{
public:
	EndSceneEiwi() :Obj(OT_TRANSPARENCY, 0.9f)
	{
		Init();
	}

	~EndSceneEiwi()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("Eiwi"), _T("2DTextures/End/End_Eiwi.jpg"));
	}

	inline VOID Update() {};

	VOID Render();
};

#endif	//! END_SCENE_OBJ_H
