/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#include "ResultSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"

VOID ResultDataScore::Render()
{
	RenderCase();

	SceneManager& rSceneManager = SceneManager::GetInstance();
	if (!rSceneManager.LatterTransitionStagingIsEnded()) return;

	INT stagingScore = static_cast<INT>(m_SCORE * (static_cast<FLOAT>(m_increaseStagingCount) / m_INCREASE_STAGING_MAX));

	INT stagingScoreDigitsNum = static_cast<INT>(log10(stagingScore) + 1);

	INT* pDigitNum = nullptr;

	const INT DIGIT_OVER = 10;

	const FLOAT DIGIT_HALF_SCALE = m_WND_SIZE.m_y * 0.07f;
	const FLOAT DIGIT_POS_Y_GAP	= DIGIT_HALF_SCALE * 1.0f;

	ObjData* pDigitScoreData = nullptr;

	const FLOAT NUMS_ILLUST_SCALE = 32.0f;
	const INT NUMS_NUM_IN_ROW		= 8;
	const INT NUMS_NUM_IN_COLUMN	= 2;

	CustomVertex* pDigitScore = nullptr;

	for (INT i = 0; m_digitsNum; ++i)
	{
		if (i + 1 > stagingScoreDigitsNum) break;

		pDigitNum = &m_digitScoresVec[i].m_num;
		*pDigitNum = (stagingScore / static_cast<INT>(pow(DIGIT_OVER, i))) % DIGIT_OVER;

		pDigitScoreData = &m_digitScoresVec[i].m_objData;
		pDigitScoreData->m_center		= { m_WND_SIZE.m_x * 0.8f - DIGIT_POS_Y_GAP * i, m_WND_SIZE.m_y * 0.26f, m_Z };	//! 現物合わせ
		pDigitScoreData->m_halfScale	= { DIGIT_HALF_SCALE, DIGIT_HALF_SCALE, 0.0f };

		pDigitScoreData->m_texUV =																						//! 統合ファイルのテクスチャの座標
		{
			NUMS_ILLUST_SCALE * ((*pDigitNum) % NUMS_NUM_IN_ROW)		/ (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW),
			NUMS_ILLUST_SCALE * ((*pDigitNum) / NUMS_NUM_IN_ROW)		/ (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN),
			NUMS_ILLUST_SCALE * ((*pDigitNum) % NUMS_NUM_IN_ROW + 1)	/ (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW),
			NUMS_ILLUST_SCALE * ((*pDigitNum) / NUMS_NUM_IN_ROW + 1)	/ (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN),
		};

		pDigitScore = m_digitScoresVec[i].m_customVertices;
		m_rGameLib.CreateRect(pDigitScore, *pDigitScoreData);

		m_rGameLib.Render(pDigitScore, m_rGameLib.GetTex(_T("Nums")));
	}

	++m_increaseStagingCount;

	if (m_increaseStagingCount < m_INCREASE_STAGING_MAX) return;
		
	m_increaseStagingCount = m_INCREASE_STAGING_MAX;

	m_stagingIsEnd = TRUE;
}

VOID ResultDataClearStar::Render()
{
	RenderCase();

	const INT FRAME_ONE_STAR_TAKES = 15;

	ObjData* pStarData = nullptr;

	const INT DEFAULT_STARS_ROW_MAX = 8;
	const FLOAT STAR_HALF_SCALE = m_WND_SIZE.m_x * 0.03f;

	INT* pAlphaCount = nullptr;

	BYTE alpha = NULL;

	CustomVertex* pStar = nullptr;

	for (INT i = 0; i < m_CLEAR_STARS_MAX; ++i)
	{
		pStarData = &m_starsVec[i].m_objData;
		pStarData->m_center =
		{
			m_WND_SIZE.m_x * 0.65f + 2 * STAR_HALF_SCALE * (i % (DEFAULT_STARS_ROW_MAX / 2)),	//! 現物合わせ
			m_WND_SIZE.m_y * 0.7f + 2 * STAR_HALF_SCALE * (i / (DEFAULT_STARS_ROW_MAX / 2)),	//! 現物合わせ
			m_Z
		};

		pStarData->m_halfScale = { STAR_HALF_SCALE ,STAR_HALF_SCALE, 0.0f };

		pAlphaCount = &m_starsVec[i].m_alphaCount;

		if (i < (m_stagingCount / FRAME_ONE_STAR_TAKES))
		{
			*pAlphaCount = (*pAlphaCount >= FRAME_ONE_STAR_TAKES) ? FRAME_ONE_STAR_TAKES : *pAlphaCount + 1;
			alpha = static_cast<INT>(255 * (static_cast<FLOAT>(*pAlphaCount) / FRAME_ONE_STAR_TAKES));

			pStarData->m_aRGB = D3DCOLOR_ARGB(alpha, 0xFF, 0xFF, 0xFF);
		}

		pStar = m_starsVec[i].m_customVertices;

		m_rGameLib.CreateRect(pStar, *pStarData);
		m_rGameLib.Render(pStar, m_rGameLib.GetTex(_T("Star")));
	}

	m_stageCountMax = FRAME_ONE_STAR_TAKES * m_CLEAR_STARS_NUM;

	if (m_stagingCount) ++m_stagingCount;																//!演出の起動は他クラスで行う

	if (m_stagingCount < m_stageCountMax) return;

	m_stagingCount = m_stageCountMax;

	m_stagingIsEnd = TRUE;
}

VOID ResultSceneResultFont::Render()
{
	DarkenFontAround();

	ObjData resultFontData;
	resultFontData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	resultFontData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.14f, 0.0f };	//! 現物合わせ

	BYTE alpha = static_cast<BYTE>(255 * static_cast<FLOAT>(m_alphaCount) / m_ADDITIONAL_ALPHA_FRAME);
	resultFontData.m_aRGB = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	const FLOAT ILLUST_Y_SCALE = 512.0f;
	const FLOAT RESULT_Y_SCALE = 200.0f;

	resultFontData.m_texUV =
	{
		0.0f,
		RESULT_Y_SCALE * m_IS_FAILED / ILLUST_Y_SCALE,
		1.0f,
		RESULT_Y_SCALE * (m_IS_FAILED + 1) / ILLUST_Y_SCALE
	};

	CustomVertex resultFont[4];
	m_rGameLib.CreateRect(resultFont, resultFontData);

	m_rGameLib.Render(resultFont, m_rGameLib.GetTex(_T("ResultFont")));

	m_alphaCount = (m_alphaCount >= m_ADDITIONAL_ALPHA_FRAME) ? m_ADDITIONAL_ALPHA_FRAME : ++m_alphaCount;
}

VOID ResultSceneContinue::Render()
{
	RenderFrame();

	RenderTexts();

	RenderTarget();
}

VOID ResultSceneResult::Update()
{
	m_pResultSceneResultData->Update();
	m_pResultSceneResultFont->Update();

	if (m_rGameLib.KeyboardAnyKeyIsPressed() &&
		m_pResultSceneResultData->StagingIsEnd() &&
		m_stagingGapFrameCount != m_STAGING_GAP_FRAME)
	{
		m_stagingGapFrameCount = m_STAGING_GAP_FRAME;

		return;
	}

	if (m_rGameLib.KeyboardAnyKeyIsPressed() &&
		!m_shouldShowContinue &&
		m_stagingGapFrameCount == m_STAGING_GAP_FRAME)
	{
		m_shouldShowContinue = TRUE;

		return;
	}

	if (m_shouldShowContinue) m_pResultSceneContinue->Update();
}
