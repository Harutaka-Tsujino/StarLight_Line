/// @file TitleSceneObj.h
/// <summary>
/// タイトルシーンで用いるオブジェクト継承クラスのヘッダ
/// </summary>
/// @author Harutaka-Tsujino

#ifndef TITLE_SCENE_OBJ_H
#define TITLE_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>

#include <thread>

#include "../Obj.h"
#include "../../../../../../../GameLib/GameLib.h"
#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"
#include "../../../Enum/SCENE_KIND.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Text.h"

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

	inline VOID Init()
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
		m_rGameLib.AddSoundFile(_T("Sounds/Title/TeamLogo.mp3"), _T("TeamLogo"));
		m_rGameLib.CreateTex(_T("Logo"), _T("2DTextures/Title/TitleLogo.png"));
	}

	inline VOID Update() {};

	VOID Render();
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
		m_rGameLib.AddSoundFile(_T("Sounds/Title/AnyKeyPressed.mp3"), _T("AnyKeyPressed"));
		m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/StageSelect/ChangeStage.mp3"), _T("ChangeStage"));
		m_rGameLib.CreateTex(_T("InputPrompt"), _T("2DTextures/Title/TitleWaitInput.png"));
	}

	inline VOID Update()
	{
		if (m_rGameLib.KeyboardAnyKeyIsPressed() && m_isActive)
		{
			m_rGameLib.OneShotStartSound(_T("AnyKeyPressed"));
			m_isActive = FALSE;
		}
	}

	inline VOID Render()
	{
		if (!m_isActive) return;

		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.75f, m_Z };		//! 現物合わせ
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.077f, m_WND_SIZE.m_y * 0.04f, 0.0f };	//! 現物合わせ

		data.m_aRGB = D3DCOLOR_ARGB(
						Flash(),
						255, 255, 255);

		CustomVertex inputPrompt[4];
		m_rGameLib.CreateRect(inputPrompt, data);

		m_rGameLib.Render(inputPrompt, m_rGameLib.GetTex(_T("InputPrompt")));
	}

private:
	inline BYTE Flash() const
	{
		const INT CNT_MAX = 127;
		static INT cnt = CNT_MAX;

		const INT ALPHA_MIN = 30;
		BYTE alpha = static_cast<int>(cnt * 1.5f) + ALPHA_MIN;	//! 現物合わせ

		static BOOL canIncrease = FALSE;
		if (cnt <= 0 || cnt >= CNT_MAX) canIncrease = !cnt;
		cnt += (canIncrease) ? +1 : -1;

		return alpha;
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

	inline VOID Init()
	{
		m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/Title/SelectMenu.mp3"), _T("SelectMenu"));
		m_rGameLib.CreateTex(_T("JoyCon"), _T("2DTextures/Title/Joycon.png"));
		m_rGameLib.CreateTex(_T("ConnectionPrompt"), _T("2DTextures/Title/PromptConnection.png"));
		m_rGameLib.CreateTex(_T("PlayStyle"), _T("2DTextures/Title/PlayStyle.png"));
		m_rGameLib.CreateTex(_T("NewGame"), _T("2DTextures/Title/TitleMenuNewGame.png"));
		m_rGameLib.CreateTex(_T("LoadGame"), _T("2DTextures/Title/TitleMenuLoadGame.png"));
		m_rGameLib.CreateTex(_T("EndGame"), _T("2DTextures/Title/TitleMenuEndGame.png"));
		m_rGameLib.CreateTex(_T("PlayStylePlate"), _T("2DTextures/Title/PlayStylePlate_128_64.png"));
	}	

	inline VOID Update()
	{
		if (m_rGameLib.KeyboardAnyKeyIsPressed() && !m_isActive)
		{
			m_isActive = TRUE;

			return;
		}

		if (!m_shouldSelectPlayMode)
		{
			SelectMode();

			return;
		}

		if (m_is2P)
		{
			Transfar2PWhenJoyconIsConnected();

			return;
		}

		SelectMenu();
	}

	VOID Render();

private:
	enum MENU_KIND
	{
		MK_NEW_GAME,
		MK_LOAD_GAME,
		MK_END_GAME,
		MK_MAX
	};

	enum PLAY_MODE
	{
		PM_1P,
		PM_2P,
		PM_MAX
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

	VOID SelectMode();

	VOID Transfar2PWhenJoyconIsConnected();

	VOID SelectModeRender();

	VOID ConnectPromptRender();

	VOID ConnectJoyconRender();

	//別スレッドで回す関数
	//Joyconがつながるまで回す
	VOID CheakConnectJoycon()
	{
		while(!m_rGameLib.GetIsConnectJoycon(Joycon::LEFT_CONTROLLER) ||
			  !m_rGameLib.GetIsConnectJoycon(Joycon::RIGHT_CONTROLLER))
		{
			m_rGameLib.ConnectJoycon(Joycon::LEFT_CONTROLLER);
			m_rGameLib.ConnectJoycon(Joycon::RIGHT_CONTROLLER);

			if (m_isAborted)
			{
				m_isFinished = TRUE;

				return;
			}
		}

		return;
	}

	MENU_KIND m_menuReel[MK_MAX] = { MK_NEW_GAME, MK_LOAD_GAME, MK_END_GAME };
	const INT m_CENTER_MENU = 1;
	
	PLAY_MODE m_mode = PM_1P;
	
	std::thread m_JoyconThread;

	BOOL m_isActive = FALSE;
	BOOL m_shouldSelectPlayMode = FALSE;
	BOOL m_is2P = FALSE;
	BOOL m_isAborted = FALSE;
	BOOL m_isFinished = FALSE;
};

class TitleCometEffect :public Obj
{
public:
	explicit TitleCometEffect(BOOL isInfinity = FALSE) :Obj(OT_TRANSPARENCY, 0.99f), m_isInfinityMode(isInfinity)
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

	BOOL m_isInfinityMode = FALSE;
};

class TitleSmallStarEffect :public Obj
{
public:
	TitleSmallStarEffect() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~TitleSmallStarEffect()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.CreateTex(_T("SmallStar"), _T("2DTextures/Title/SmallStarEffect.png"));
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
