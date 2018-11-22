#include "StageSelectSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

VOID StageSelectSceneStageList::Render()
{
	D3DXVECTOR3 STAGE_ICONS_CENTER_POS = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };

	const FLOAT DISTANCE_BETWEEN_CENTER_TO_STAGE_ICON = 250.0f;

	const FLOAT DEG_GAP = 360.0f / m_STAGE_ICON_MAX;

	D3DXVECTOR3* pCenter = nullptr;
	FLOAT halfScale = 0.0f;

	FLOAT* pDeg = nullptr;
	D3DXMATRIX rotate;

	const RectSize ILLUST_SIZE = { 2048, 1024 };
	const FLOAT ICON_ILLUST_SIZE = 300.0f;

	static FLOAT totalRotatedDeg = 0.0f;

	StageIconData stageIconDatas[m_STAGE_ICON_MAX];
	CustomVertex stageIcon[4];
	for (int i = 0; i < m_STAGE_ICON_MAX; ++i)
	{
		pDeg = &stageIconDatas[i].m_deg;

		*pDeg = DEG_GAP * i + totalRotatedDeg + m_deg;
		D3DXMatrixRotationZ(&rotate, D3DXToRadian(*pDeg));

		pCenter = &stageIconDatas[i].m_objData.m_center;
		pCenter->y = DISTANCE_BETWEEN_CENTER_TO_STAGE_ICON;

		D3DXVec3TransformCoord(pCenter, pCenter, &rotate);

		*pCenter += STAGE_ICONS_CENTER_POS;

		halfScale = 17.5f * (cos(D3DXToRadian(*pDeg)) + 2.0f);
		stageIconDatas[i].m_objData.m_halfScale = { halfScale, halfScale, 0.0f };

		stageIconDatas[i].m_objData.m_texUV =
		{
			ICON_ILLUST_SIZE * (i % 6)		/ ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / 6)		/ ILLUST_SIZE.m_y,
			ICON_ILLUST_SIZE * (i % 6 + 1)	/ ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / 6 + 1)	/ ILLUST_SIZE.m_y
		};

		m_rGameLib.CreateRect(stageIcon, stageIconDatas[i].m_objData);

		m_rGameLib.Render(stageIcon, m_rGameLib.GetTex(_T("Icons")));

		if (m_deg != DEG_GAP && m_deg != -DEG_GAP) continue;

		totalRotatedDeg += m_deg;
		m_deg = 0.0f;
	}
}
