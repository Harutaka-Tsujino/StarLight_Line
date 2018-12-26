#ifndef PLAYER_EFFECT_H_
#define PLAYER_EFFECT_H_

#include <windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "../../../Obj.h"
#include "../../../../../../../../../GameLib/GameLib.h"

class PlayerEffect :public Obj
{
public:
	PlayerEffect() :Obj(OT_TRANSPARENCY, 1.0f)
	{
		Init();
	}

	~PlayerEffect()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("YellowHole"), _T("2DTextures/Main/Effects/YellowHole.png"));
	}

	inline VOID Update() {};

	inline VOID Render()
	{
		//m_rGameLib.AddtionBlendMode();

		ObjData data;
		data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };

		const FLOAT HALF_SCALE = m_WND_SIZE.m_x * 0.2f;

		data.m_halfScale = { HALF_SCALE, HALF_SCALE, 0.0f };

		CustomVertex Effect[4];
		m_rGameLib.CreateRect(Effect, data);

		m_rGameLib.Render(Effect, m_rGameLib.GetTex(_T("YellowHole")));

		m_rGameLib.DefaultBlendMode();
	}
};

#endif // !

