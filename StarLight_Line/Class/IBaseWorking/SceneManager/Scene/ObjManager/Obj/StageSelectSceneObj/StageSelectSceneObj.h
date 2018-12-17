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
		m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/Title/title_background.png"));
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
	}

	~StageSelectSceneStageList()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("Icons"), _T("2DTextures/StageSelect/StageSelect_icons.png"));
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
		m_lengthMulti = 1.0f;

		m_isDecided = FALSE;
	}

	inline INT GetStage() const
	{
		return m_selectingStage;
	}

private:
	struct StageIconData
	{
		ObjData m_objData;
		FLOAT m_deg;
	};

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

	static const INT m_STAGE_ICONS_MAX = 12;
	FLOAT m_deg = 0.0f;			//! 複数のアイコンがなす円の回転角度 大きさが60を超えるとm_selectingStageを変化させ0に戻る

	INT m_selectingStage = 0;

	FLOAT m_lengthMulti = 0.0f;	//! 毎フレーム複数のアイコンがなす円の半径を変化させるときに加える長さの倍率

	BOOL m_isDecided = FALSE;

	BOOL m_backIsSelected = FALSE;
};

class StageSelectSceneLevelSelecter :public Obj
{
public:
	StageSelectSceneLevelSelecter(const BOOL& m_stageIsDecided) :Obj(OT_TRANSPARENCY, 9.0f), m_rStageIsDecided(m_stageIsDecided)
	{
		Init();
	}

	~StageSelectSceneLevelSelecter()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.CreateTex(_T("LevelBack"), _T("2DTextures/StageSelect/StageSelect_difficultyBack.png"));
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

private:
	VOID RenderBack() const;

	VOID RenderTarget() const;

	VOID RenderBackButton() const;

	const BOOL& m_rStageIsDecided;

	INT m_level = SLK_EASY;
	
	INT m_alpha = 0;

	BOOL m_backIsSelected = FALSE;
	BOOL m_shouldActivateStageSelect = FALSE;
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
		m_pLevelSelecter->Update();
	}

	inline VOID Render()
	{
		m_pLevelSelecter->Render();
		m_pStageList->Render();
	}

	inline VOID SendStageDataToSceneManager()
	{
		m_pStageList->GetStage();
		m_pLevelSelecter->Level();

		StageData StageData = { m_pStageList->GetStage(), m_pLevelSelecter->Level() };

		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.SetStageData(StageData);
	}

private:
	StageSelectSceneStageList* m_pStageList = nullptr;
	StageSelectSceneLevelSelecter* m_pLevelSelecter = nullptr;
};

#endif // !STAGE_SELECT_SCENE_OBJ_H
