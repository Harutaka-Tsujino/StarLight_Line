#ifndef TUTORIAL_SCENE_OBJ_H
#define TUTORIAL_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../MainSceneObj/StarManager/StarManager.h"
#include "../../../../SceneManager.h"

#include <crtdbg.h>

#include <cstdio>
#include <cstdlib>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

class TutorialSlides :public Obj
{
public:
	TutorialSlides() :Obj(OT_OPACITY, 0.0f)
	{
		Init();
	}

	~TutorialSlides()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("Slide0"), _T("2DTextures/Tutorial/tutorial.jpg"));
		m_rGameLib.CreateTex(_T("Slide1"), _T("2DTextures/Tutorial/tutorial2.jpg"));
		m_rGameLib.CreateTex(_T("Slide2"), _T("2DTextures/Tutorial/tutorial3.jpg"));
	}

	inline VOID Update()
	{
		if (m_currentTexNum == m_TEX_MAX - 1 && ReturnKeyIsPressed())
		{
			m_ends = TRUE;

			return;
		}

		if (m_rGameLib.KeyboardIsPressed(DIK_A))	m_currentTexNum = max(m_currentTexNum - 1, 0);
		if (ReturnKeyIsPressed())					m_currentTexNum = min(m_currentTexNum + 1, m_TEX_MAX - 1);
	}

	inline VOID Render()
	{
		m_rGameLib.SetCameraTransform();

		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex slide[4];
		m_rGameLib.CreateRect(slide, data);

		const TCHAR* pKey[m_TEX_MAX] = { _T("Slide0"),_T("Slide1"),_T("Slide2") };

		m_rGameLib.Render(slide, m_rGameLib.GetTex(pKey[m_currentTexNum]));
	}

	inline BOOL Ends() const
	{
		return m_ends;
	}

private:
	static const INT m_TEX_MAX = 3;
	INT m_currentTexNum = 0;

	BOOL m_ends = FALSE;
};

class TutorialManager :public Obj
{
public:
	TutorialManager() :Obj(OT_OPACITY, 0.0f)
	{
		Init();
	}

	~TutorialManager()
	{
		delete m_pTutorialSlides;
		delete m_pStarManager;
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		SceneManager::GetInstance().SetIsTutorial(TRUE);

		m_pStarManager = new StarManager();
		m_rGameLib.StopTime();
		m_pTutorialSlides = new TutorialSlides();

		m_rGameLib.CreateTex(_T("Conv0"), _T("2DTextures/Tutorial/EiwiConv1.png"));
		m_rGameLib.CreateTex(_T("Conv1"), _T("2DTextures/Tutorial/EiwiConv2.png"));
		m_rGameLib.CreateTex(_T("Conv2"), _T("2DTextures/Tutorial/EiwiConv3.png"));
		m_rGameLib.CreateTex(_T("Conv3"), _T("2DTextures/Tutorial/EiwiConv4.png"));
		m_rGameLib.CreateTex(_T("YesNo"), _T("2DTextures/Result/YesNo.png"));
		m_rGameLib.CreateTex(_T("Target"), _T("2DTextures/Result/Target.png"));
	}

	VOID Update();

	VOID Render();

private:
	enum EIWI_CONV
	{
		E_CONV_GREETING,
		E_CONV_TUTORIAL_SUGGESTING,
		E_CONV_PLAY_START,
		E_CONV_PLAY_END,
		E_CONV_MAX
	};

	inline VOID RenderTexts() const
	{
		ObjData YesNoData;
		YesNoData.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };

		const FLOAT HALF_SCALE = m_WND_SIZE.m_y * 0.22f;
		YesNoData.m_halfScale = { HALF_SCALE, HALF_SCALE, 0.0f };

		CustomVertex YesNo[4];
		m_rGameLib.CreateRect(YesNo, YesNoData);

		m_rGameLib.Render(YesNo, m_rGameLib.GetTex(_T("YesNo")));
	}

	inline VOID RenderTarget()
	{
		ObjData targetData;

		const FLOAT CENTER_Y_WND_MULTI_BASE = 0.423f;
		FLOAT centerYWndMulti	= (m_yesIsSelected) ? CENTER_Y_WND_MULTI_BASE : CENTER_Y_WND_MULTI_BASE + 0.158f;
		targetData.m_center		= { m_WND_SIZE.m_x * 0.4f, m_WND_SIZE.m_y * centerYWndMulti, m_Z }; //! 現物合わせ

		const FLOAT TARGET_HALF_SCALE = m_WND_SIZE.m_x * 0.02f;
		targetData.m_halfScale		  = { TARGET_HALF_SCALE, TARGET_HALF_SCALE, 0.0f };

		CustomVertex target[4];
		m_rGameLib.CreateRect(target, targetData);

		m_rGameLib.Render(target, m_rGameLib.GetTex(_T("Target")));
	}

	static const INT m_TEX_MAX = 3;
	INT m_currentConvNum = 0;

	BOOL m_yesIsSelected = TRUE;
	BOOL m_firstConvPartEnds = FALSE;
	BOOL m_tutorialIsPlayed = FALSE;

	StarManager* m_pStarManager = nullptr;
	TutorialSlides* m_pTutorialSlides = nullptr;
};

#endif //! TUTORIAL_SCENE_OBJ_H
