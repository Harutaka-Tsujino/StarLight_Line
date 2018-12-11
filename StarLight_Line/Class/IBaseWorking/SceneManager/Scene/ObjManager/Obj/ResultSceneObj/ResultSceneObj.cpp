#include "ResultSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"

VOID ResultDataScore::Render()
{
	if (m_increaseStageCount < 0)
	{
		++m_increaseStageCount;

		return;
	}

	const INT INCREASE_STAGE_MAX = 150;

	INT stageScore = static_cast<INT>(m_SCORE * (static_cast<FLOAT>(m_increaseStageCount) / INCREASE_STAGE_MAX));

	INT stageScoreDigitsNum = static_cast<INT>(log10(stageScore) + 1);

	if (!stageScore) stageScoreDigitsNum = 0;

	INT* pDigitNum = nullptr;

	INT DIGIT_OVER = 10;

	const FLOAT DIGIT_HALF_SCALE = m_WND_SIZE.m_y * 0.07f;
	const FLOAT DIGIT_POS_Y_GAP	= DIGIT_HALF_SCALE * 1.0f;

	ObjData* pDigitScoreData = nullptr;

	const FLOAT NUMS_ILLUST_SCALE = 32.0f;
	const INT NUMS_NUM_IN_ROW		= 8;
	const INT NUMS_NUM_IN_COLUMN	= 2;

	CustomVertex* pDigitScore = nullptr;

	for (INT i = 0; m_digitsNum; ++i)
	{
		if (i + 1 > stageScoreDigitsNum) break;

		pDigitNum = &m_digitScoresVec[i].m_num;
		*pDigitNum = (stageScore / static_cast<INT>(pow(DIGIT_OVER, i))) % DIGIT_OVER;

		pDigitScoreData = &m_digitScoresVec[i].m_objData;
		pDigitScoreData->m_center		= { m_WND_SIZE.m_x * 0.8f - DIGIT_POS_Y_GAP * i, m_WND_SIZE.m_y * 0.3f, m_Z };	//現物合わせ
		pDigitScoreData->m_halfScale	= { DIGIT_HALF_SCALE, DIGIT_HALF_SCALE, 0.0f };

		pDigitScoreData->m_texUV =															//! 統合ファイルのテクスチャの座標
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

	m_increaseStageCount = (m_increaseStageCount >= INCREASE_STAGE_MAX) ? INCREASE_STAGE_MAX : ++m_increaseStageCount;

	if (m_increaseStageCount >= INCREASE_STAGE_MAX) m_stagingIsEnd = TRUE;
}

VOID ResultDataClearStar::Render()
{
	const INT COUNT_STAR_TAKES = 15;

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
			m_WND_SIZE.m_x * 0.5f + 2 * STAR_HALF_SCALE * (i % (DEFAULT_STARS_ROW_MAX / 2)),
			m_WND_SIZE.m_y * 0.5f + 2 * STAR_HALF_SCALE * (i / (DEFAULT_STARS_ROW_MAX / 2)),
			m_Z
		};

		pStarData->m_halfScale = { STAR_HALF_SCALE ,STAR_HALF_SCALE, 0.0f };

		pAlphaCount = &m_starsVec[i].m_alphaCount;

		if (m_stagingCount && (i <= (m_stagingCount / COUNT_STAR_TAKES)) && !m_stagingIsEnd)
		{
			*pAlphaCount = (*pAlphaCount >= COUNT_STAR_TAKES) ? COUNT_STAR_TAKES : ++(*pAlphaCount);
			alpha = static_cast<BYTE>(255 * (static_cast<FLOAT>(*pAlphaCount) / COUNT_STAR_TAKES));

			pStarData->m_aRGB = D3DCOLOR_ARGB(alpha, 0xFF, 0xFF, 0xFF);
		}

		pStar = m_starsVec[i].m_customVertices;

		m_rGameLib.CreateRect(pStar, *pStarData);
		m_rGameLib.Render(pStar, m_rGameLib.GetTex(_T("Star")));
	}

	const INT STAGE_COUNT_MAX = COUNT_STAR_TAKES * m_CLEAR_STARS_NUM;

	if (!m_stagingCount) return;

	m_stagingCount = (m_stagingCount >= STAGE_COUNT_MAX) ? STAGE_COUNT_MAX : ++m_stagingCount;

	if (m_stagingCount >= STAGE_COUNT_MAX) m_stagingIsEnd = TRUE;
}

VOID ResultSceneResultFont::Render()
{
	ObjData blackMaskData;
	blackMaskData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	blackMaskData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	blackMaskData.m_aRGB = 0x55000000;

	CustomVertex blackMask[4];
	m_rGameLib.CreateRect(blackMask, blackMaskData);

	m_rGameLib.Render(blackMask, nullptr);

	ObjData resultFontData;
	resultFontData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	resultFontData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.14f, 0.0f };

	const FLOAT ILLUST_Y_SCALE = 512.0f;
	const FLOAT RESULT_Y_SCALE = 200.0f;

	resultFontData.m_texUV =
	{
		0.0f,
		RESULT_Y_SCALE * m_isFailed / ILLUST_Y_SCALE,
		1.0f,
		RESULT_Y_SCALE * (m_isFailed + 1) / ILLUST_Y_SCALE
	};

	CustomVertex resultFont[4];
	m_rGameLib.CreateRect(resultFont, resultFontData);

	m_rGameLib.Render(resultFont, m_rGameLib.GetTex(_T("ResultFont")));
}

VOID ResultSceneContinue::Render()
{
	ObjData ContinueFrameData;
	ContinueFrameData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	ContinueFrameData.m_halfScale	= { m_WND_SIZE.m_x * 0.28f, m_WND_SIZE.m_y * 0.28f, 0.0f };

	CustomVertex ContinueFrame[4];
	m_rGameLib.CreateRect(ContinueFrame, ContinueFrameData);

	m_rGameLib.Render(ContinueFrame, m_rGameLib.GetTex(_T("ContinueFrame")));

	ObjData YesNoData;
	YesNoData.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };

	const FLOAT HALF_SCALE = m_WND_SIZE.m_y * 0.22f;
	YesNoData.m_halfScale = { HALF_SCALE, HALF_SCALE, 0.0f };

	CustomVertex YesNo[4];
	m_rGameLib.CreateRect(YesNo, YesNoData);

	m_rGameLib.Render(YesNo, m_rGameLib.GetTex(_T("YesNo")));
}
