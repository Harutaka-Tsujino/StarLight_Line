/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#ifndef STAGE_SELECT_SCENE_OBJ_H
#define STAGE_SELECT_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../StageSelectScene/Enum/STAGE_LEVEL_KIND.h"
#include "../../../StageSelectScene/Enum/STAGE_KIND.h"
#include "../../../../SceneManager.h"
#include "../../../../Data/StageData.h"

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
		m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/StageSelect/StageSelectBack.png"));
	}

	inline VOID Update() {};

	inline VOID Render()
	{
		m_rGameLib.SetCameraTransform();

		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };	//! 現物合わせ
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };	//! 現物合わせ

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

		StageData stageData;
		SceneManager::GetInstance().GetStageData(&stageData);
	}

	~StageSelectSceneStageList()
	{
		m_blackHoleIsSelected = FALSE;

		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.CreateTex(_T("Icons"), _T("2DTextures/StageSelect/StageSelect_icons.png"));
		m_rGameLib.CreateTex(_T("BlackHoleIcon"), _T("2DTextures/StageSelect/BlackHoleIcon.png"));
		m_rGameLib.CreateTex(_T("BackButton"), _T("2DTextures/StageSelect/StageSelect_BackButton.png"));
	}

	VOID Update();

	VOID Render();

	inline const BOOL& IsDecided() const
	{
		return m_isDecided;
	}

	inline VOID ActivateStageSelect()
	{
		m_isDecided = FALSE;

		if (m_blackHoleIsSelected) return;

		m_lengthMulti = 1.0f;
	}

	inline INT GetStage() const
	{
		if (m_blackHoleIsSelected) return STAGE_BLACK_HOLE;

		return m_selectingStage;
	}

	inline BOOL BlackHoleIconSelected()
	{
		return m_blackHoleIsSelected;
	}

private:
	struct StageIconData
	{
		ObjData m_objData;
		FLOAT m_deg;
	};

	inline VOID RenderBlackHole()
	{
		static ObjData data;
		data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.4f, m_Z };

		const FLOAT BLACK_HOLE_RADIUSU_MAX = 540.0f;

		const INT DECIDE_STAGE_FRAMES = 60;

		auto StageBlackHole = [&, this]()
		{
			if (!m_blackHoleIsSelected)
			{
				if (m_lengthMulti == 0 && !m_isDecided) m_blackHoleAlpha += (255 / 60);

				m_blackHoleAlpha += static_cast<INT>(m_lengthMulti * (255 / 60));

				m_blackHoleRadius -= BLACK_HOLE_RADIUSU_MAX / DECIDE_STAGE_FRAMES;

				return;
			}

			m_blackHoleRadius += BLACK_HOLE_RADIUSU_MAX / DECIDE_STAGE_FRAMES;
		};

		StageBlackHole();

		m_blackHoleRadius = min(max(m_blackHoleRadius, m_BLACK_HOLE_RADIUSU_MIN), BLACK_HOLE_RADIUSU_MAX);

		m_blackHoleStagingEnds = FALSE;

		if (m_blackHoleRadius == BLACK_HOLE_RADIUSU_MAX) m_blackHoleStagingEnds = TRUE;

		data.m_halfScale = { m_blackHoleRadius, m_blackHoleRadius, 0.0f };

		m_blackHoleAlpha = min(max(m_blackHoleAlpha, 0), 255);
		data.m_aRGB = D3DCOLOR_ARGB(m_blackHoleAlpha, 255, 255, 255);

		data.m_deg.z += 0.25f;

		CustomVertex blackHole[4];
		m_rGameLib.CreateRect(blackHole, data);
		m_rGameLib.Render(blackHole, m_rGameLib.GetTex(_T("BlackHoleIcon")));
	}

	inline VOID RotateIconsCenter(StageIconData* pStageIconDatas, INT iconElementNum, FLOAT degGap, FLOAT iconsCircleRadius)
	{
		const D3DXVECTOR3 ICONS_CENTER = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.4f, m_Z };	//! 現物合わせ

		D3DXMATRIX rotate;
		
		FLOAT* pDeg = nullptr;
		pDeg = &pStageIconDatas[iconElementNum].m_deg;
		*pDeg = degGap * (iconElementNum - m_selectingStage) + m_deg;
		D3DXMatrixRotationZ(&rotate, D3DXToRadian(*pDeg));

		D3DXVECTOR3* pCenter = nullptr;
		pCenter = &pStageIconDatas[iconElementNum].m_objData.m_center;
		pCenter->y = iconsCircleRadius;
		D3DXVec3TransformCoord(pCenter, pCenter, &rotate);
		*pCenter += ICONS_CENTER;
	}

	inline VOID SetHalfScaleByRadius(StageIconData* pStageIconDatas, INT iconElementNum, FLOAT iconsCircleRadius, FLOAT iconsCircleRadiusMax)
	{
		FLOAT iconScaleMulti = cos(D3DXToRadian(pStageIconDatas[iconElementNum].m_deg)) + 2.0f;				//! 1～3までの拡大率を角度によって決める
		FLOAT halfScale = (((iconsCircleRadiusMax - iconsCircleRadius) * 0.01f) + 17.5f) * iconScaleMulti;	//! (最大値との半径の差 * 半径の差が大きくなりすぎるので縮小倍率 + 半径の最小の値) * 角度によるアイコンの拡大率

		if (iconElementNum == m_selectingStage)
		{
			halfScale += m_WND_SIZE.m_y * 0.06f * (1.0f - (iconsCircleRadius / iconsCircleRadiusMax));		//! 現物合わせ
		}

		pStageIconDatas[iconElementNum].m_objData.m_halfScale = { halfScale, halfScale, 0.0f };
	}

	VOID RenderBackButton(FLOAT iconsCircleRadius) const;

	static const INT m_STAGE_ICONS_MAX = STAGE_MAX - 1;

	FLOAT m_deg = 0.0f;			//! 複数のアイコンがなす円の回転角度 大きさが60を超えるとm_selectingStageを変化させ0に戻る

	INT m_selectingStage = 0;

	static const FLOAT m_ICONS_CIRCLE_RADIUS_MAX;	//! 複数のアイコンがなす円の半径の最大値
	FLOAT m_iconsCircleRadius = m_ICONS_CIRCLE_RADIUS_MAX;	//! 複数のアイコンがなす円の半径
	FLOAT m_lengthMulti = 0.0f;	//! 毎フレーム複数のアイコンがなす円の半径を変化させるときに加える長さの倍率

	BOOL m_isDecided = FALSE;

	BOOL m_blackHoleIsSelected = FALSE;
	BOOL m_blackHoleStagingEnds = FALSE;

	INT m_blackHoleAlpha = 0;
	static const FLOAT m_BLACK_HOLE_RADIUSU_MIN;
	FLOAT m_blackHoleRadius = m_BLACK_HOLE_RADIUSU_MIN;

	BOOL m_backIsSelected = FALSE;
};

class StageSelectSceneLevelSelecter :public Obj
{
public:
	StageSelectSceneLevelSelecter(const BOOL& m_stageIsDecided) :Obj(OT_TRANSPARENCY, 0.91f), m_rStageIsDecided(m_stageIsDecided)
	{
		Init();
	}

	~StageSelectSceneLevelSelecter()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.CreateTex(_T("LevelBack"), _T("2DTextures/StageSelect/StageSelectLevelBack.png"));
		m_rGameLib.CreateTex(_T("LevelTexts"), _T("2DTextures/StageSelect/LevelTexts.png"));
		m_rGameLib.CreateTex(_T("LevelTarget"), _T("2DTextures/Result/Target.png"));
		m_rGameLib.CreateTex(_T("LevelBackButton"), _T("2DTextures/StageSelect/difficultyselect_backicon.png"));
	}

	VOID Update();

	VOID Render();

	inline BOOL ShouldActivateStageSelect() const
	{
		return m_shouldActivateStageSelect;
	}

	inline INT Level() const
	{
		return m_level;
	}

	inline VOID SetBlackHoleIsSelected(BOOL isSelected)
	{
		m_blackHoleIsSelected = isSelected;
	}

private:
	VOID RenderBack() const;

	VOID RenderTarget() const;

	VOID RenderBackButton() const;

	const BOOL& m_rStageIsDecided;

	INT m_level = SLK_EASY;
	
	INT m_alpha = 0;

	BOOL m_backIsSelected = FALSE;
	BOOL m_shouldActivateStageSelect = FALSE;
	BOOL m_blackHoleIsSelected = FALSE;
};

class StageSelectSceneStages :public Obj
{
public:
	StageSelectSceneStages() :Obj(OT_TRANSPARENCY, 1.0f)
	{
		Init();
	}

	~StageSelectSceneStages()
	{
		SendStageDataToSceneManager();

		delete m_pLevelSelecter;
		delete m_pStageList;
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_pStageList = new StageSelectSceneStageList();

		m_pLevelSelecter = new StageSelectSceneLevelSelecter(m_pStageList->IsDecided());
	}

	inline VOID Update()
	{
		if (m_pLevelSelecter->ShouldActivateStageSelect()) m_pStageList->ActivateStageSelect();

		m_pStageList->Update();
		m_pLevelSelecter->SetBlackHoleIsSelected(m_pStageList->BlackHoleIconSelected());
		m_pLevelSelecter->Update();
	}

	inline VOID Render()
	{
		m_pLevelSelecter->Render();
		m_pStageList->Render();
	}

	inline VOID SendStageDataToSceneManager()
	{
		StageData StageData = { m_pLevelSelecter->Level(), m_pStageList->GetStage() };

		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.SetStageData(StageData);
	}

private:
	StageSelectSceneStageList* m_pStageList = nullptr;
	StageSelectSceneLevelSelecter* m_pLevelSelecter = nullptr;
};

#endif // !STAGE_SELECT_SCENE_OBJ_H
