#ifndef TITLE_SCENE_OBJ_H
#define TITLE_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>

#include "../Obj.h"
#include "../../../../../../../GameLib/GameLib.h"
#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"
#include "../../../Enum/SCENE_KIND.h"

class TitleBack :public Obj
{
public:
	TitleBack() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~TitleBack()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
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

class TitleLogo :public Obj
{
public:
	TitleLogo() :Obj(OT_TRANSPARENCY, 0.98f)
	{
		Init();
	}

	~TitleLogo()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("Logo"), _T("2DTextures/Title/TitleLogo.png"));
	}

	inline VOID Update() {};

	inline VOID Render()
	{
		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.35f, m_Z };
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.29f, m_WND_SIZE.m_y * 0.2f, 0.0f };

		CustomVertex logo[4];
		m_rGameLib.CreateRect(logo, data);

		m_rGameLib.Render(logo, m_rGameLib.GetTex(_T("Logo")));
	}
};

class TitleInputPrompt :public Obj
{
public:
	TitleInputPrompt() :Obj(OT_TRANSPARENCY, 0.98f)
	{
		Init();
	}

	~TitleInputPrompt()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("InputPrompt"), _T("2DTextures/Title/TitleWaitInput.png"));
	}

	inline VOID Update()
	{
		if (m_rGameLib.KeyboardAnyKeyIsPressed()) m_isActive = FALSE;
	}

	inline VOID Render()
	{
		if (!m_isActive) return;

		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.78f, m_Z };
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.07f, m_WND_SIZE.m_y * 0.035f, 0.0f };
		CustomVertex inputPrompt[4];
		data.m_aRGB = D3DCOLOR_ARGB(
						Flash(),
						255, 255, 255);
		m_rGameLib.CreateRect(inputPrompt, data);

		m_rGameLib.Render(inputPrompt, m_rGameLib.GetTex(_T("InputPrompt")));
	}

private:
	inline BYTE Flash() const
	{
		const INT CNT_MAX = 127;
		static INT cnt = CNT_MAX;

		const INT ALPHA_MIN = 30;
		BYTE aRBG = static_cast<int>(cnt * 1.5f) + ALPHA_MIN;

		static BOOL canIncrease = FALSE;
		if (cnt <= 0 || cnt >= CNT_MAX) canIncrease = !cnt;
		cnt += (canIncrease) ? +1 : -1;

		return aRBG;
	}

	BOOL m_isActive = TRUE;
};

class TitleMenu :public Obj
{
public:
	TitleMenu() :Obj(OT_TRANSPARENCY, 0.98f)
	{
		Init();
	}

	~TitleMenu()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("NewGame"), _T("2DTextures/Title/TitleMenuNewGame.png"));
		m_rGameLib.CreateTex(_T("LoadGame"), _T("2DTextures/Title/TitleMenuLoadGame.png"));
		m_rGameLib.CreateTex(_T("EndGame"), _T("2DTextures/Title/TitleMenuEndGame.png"));
	}	

	inline VOID Update()
	{
		if (m_rGameLib.KeyboardAnyKeyIsPressed()) m_isActive = TRUE;
		if (!m_isActive) return;

		SelectMenu();
	}

	inline VOID Render();

private:
	enum MENU_KIND
	{
		MK_NEW_GAME,
		MK_LOAD_GAME,
		MK_END_GAME,
		MK_MAX
	};

	inline VOID RotateMenuUp()
	{
		MENU_KIND menuReelTmp[MK_MAX] = { m_menuReel[1], m_menuReel[2],m_menuReel[0] };
		memcpy(
			&m_menuReel, 
			&menuReelTmp, 
			sizeof(MENU_KIND) * MK_MAX);
	}

	inline VOID RotateMenuDown()
	{
		MENU_KIND menuReelTmp[MK_MAX] = { m_menuReel[2], m_menuReel[0], m_menuReel[1] };
		memcpy(
			&m_menuReel, 
			&menuReelTmp, 
			sizeof(MENU_KIND) * MK_MAX);
	}

	VOID SelectMenu();

	MENU_KIND m_menuReel[MK_MAX] = { MK_END_GAME, MK_NEW_GAME, MK_LOAD_GAME };
	const INT m_CENTER_MENU = 1;
	
	BOOL m_isActive = FALSE;
};

class TitleCometEffect :public Obj
{
public:
	TitleCometEffect() :Obj(OT_TRANSPARENCY, 0.99f)
	{
		Init();
	}

	~TitleCometEffect() 
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.CreateTex(_T("Comet"), _T("2DTextures/Title/StarEffect.png"));
		m_rGameLib.CreateTex(_T("OverComet"), _T("2DTextures/Title/OverStarEffect.png"));
	}

	inline VOID Update() {};

	VOID Render();

private:
	struct EffectData
	{
	public:
		BOOL m_isInit = FALSE;
		ObjData m_data;
		D3DXVECTOR3 m_movement = { 0.0f, 0.0f, 0.0f };
		CustomVertex m_vertices[4];
	};

	VOID InitEffect(EffectData* pEffectDatas);

	BOOL m_isInitInFrame = FALSE;
};

class TitleSmallStarEffect :public Obj
{
public:
	TitleSmallStarEffect() :Obj(OT_TRANSPARENCY, 0.991f)
	{
		Init();
	}

	~TitleSmallStarEffect()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.CreateTex(_T("SmallStar"), _T("2DTextures/Title/EffectData.png"));
		m_rGameLib.CreateTex(_T("OverSmallStar"), _T("2DTextures/Title/OverSmallStarEffect.png"));
	}

	inline VOID Update() {};

	VOID Render();

private:
	struct EffectData
	{
	public:
		const INT m_INIT_CNT = -1;
		BOOL m_isIncrease = TRUE;
		INT m_flashCnt = m_INIT_CNT;
		ObjData m_data;
		D3DXVECTOR4 m_aRGB;
		CustomVertex m_vertices[4];
	};

	VOID InitEffect(EffectData* pEffectDatas) const;

	inline VOID CntFlashCnt(EffectData* pEffectDatas) const
	{
		if (pEffectDatas->m_flashCnt >= m_FLASH_CNT_MAX) pEffectDatas->m_isIncrease = FALSE;
		if (pEffectDatas->m_flashCnt <= m_FLASH_CNT_MIN) pEffectDatas->m_isIncrease = TRUE;

		pEffectDatas->m_flashCnt += 5 * ((pEffectDatas->m_isIncrease) ? 1 : -1);
	}

	const INT m_FLASH_CNT_MAX = 210;
	const INT m_FLASH_CNT_MIN = 20;
};

#endif // !TITLE_SCENE_OBJ_H
