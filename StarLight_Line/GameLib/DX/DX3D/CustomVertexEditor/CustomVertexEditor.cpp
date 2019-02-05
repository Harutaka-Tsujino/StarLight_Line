#include "CustomVertexEditor.h"

#include <windows.h>

#include <d3dx9.h>

#include "Data/CustomVertex.h"
#include "Data/ObjData.h"

VOID CustomVertexEditor::Rotate(CustomVertex* pCustomVertices, 
	const D3DXVECTOR3& rRelativeRotateCenter, const D3DXMATRIX& rRotate) const
{
	D3DXVECTOR3 rectCenter(										//対角線によってすでに回転が行われているものの中心も割り出せる
		(pCustomVertices[0].m_pos.x + pCustomVertices[2].m_pos.x) * 0.5f,
		(pCustomVertices[0].m_pos.y + pCustomVertices[2].m_pos.y) * 0.5f,
		(pCustomVertices[0].m_pos.z + pCustomVertices[2].m_pos.z) * 0.5f);

	D3DXVECTOR3 verticesRectCenterToOri[m_RECT_VERTICES_NUM];	//回転の中心は必ずしも矩形の中心ではない
	for (INT i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		verticesRectCenterToOri[i].x = pCustomVertices[i].m_pos.x - rectCenter.x;
		verticesRectCenterToOri[i].y = pCustomVertices[i].m_pos.y - rectCenter.y;
		verticesRectCenterToOri[i].z = pCustomVertices[i].m_pos.z - rectCenter.z;
	};

	D3DXVECTOR3 verticesRotateCenterToOri[m_RECT_VERTICES_NUM];
	for (INT i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		verticesRotateCenterToOri[i].x = verticesRectCenterToOri[i].x - rRelativeRotateCenter.x;
		verticesRotateCenterToOri[i].y = verticesRectCenterToOri[i].y - rRelativeRotateCenter.y;
		verticesRotateCenterToOri[i].z = verticesRectCenterToOri[i].z - rRelativeRotateCenter.z;
	};

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		D3DXVec3TransformCoord(
			&pCustomVertices[i].m_pos,
			&verticesRotateCenterToOri[i],
			&rRotate);

		D3DXVec3Add(
			&pCustomVertices[i].m_pos,
			&pCustomVertices[i].m_pos,
			&rectCenter);

		D3DXVec3Add(
			&pCustomVertices[i].m_pos,
			&pCustomVertices[i].m_pos,
			&rRelativeRotateCenter);
	}
}

VOID CustomVertexEditor::Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2& rScaleRate) const
{
	D3DXVECTOR2 rectCenter(
		(pCustomVertices[0].m_pos.x + pCustomVertices[2].m_pos.x) * 0.5f,
		(pCustomVertices[0].m_pos.y + pCustomVertices[2].m_pos.y) * 0.5f);

	D3DXVECTOR2 distancesVertexBetweenCenter[m_RECT_VERTICES_NUM];

	for (INT i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		distancesVertexBetweenCenter[i].x = pCustomVertices[i].m_pos.x - rectCenter.x;
		distancesVertexBetweenCenter[i].y = pCustomVertices[i].m_pos.y - rectCenter.y;
	};

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		pCustomVertices[i].m_pos.x = rScaleRate.x*distancesVertexBetweenCenter[i].x + rectCenter.x;
		pCustomVertices[i].m_pos.y = rScaleRate.y*distancesVertexBetweenCenter[i].y + rectCenter.y;
	}
}

VOID CustomVertexEditor::SetObliqueToBottomRightARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
{
	DWORD aveColor = 0;

	//α値を求める
	BYTE alphaValue[2] = { static_cast<BYTE>(topARGB >> 24) ,static_cast<BYTE>(bottomARGB >> 24) };
	aveColor += (((alphaValue[0] + alphaValue[1]) / 2) << 24);

	//r値を求める
	BYTE redValue[2] = { static_cast<BYTE>(topARGB >> 16) ,static_cast<BYTE>(bottomARGB >> 16) };
	aveColor += (((redValue[0] + redValue[1]) / 2) << 16);

	//g値を求める
	BYTE greenValue[2] = { static_cast<BYTE>(topARGB >> 8) ,static_cast<BYTE>(bottomARGB >> 8) };
	aveColor += (((greenValue[0] + greenValue[1]) / 2) << 8);

	//b値を求める
	BYTE blueValue[2] = { static_cast<BYTE>(topARGB) ,static_cast<BYTE>(bottomARGB) };
	aveColor += ((blueValue[0] + blueValue[1]) / 2);

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		if (i == 0)
		{
			pCustomVertices[i].m_aRGB = topARGB;

			continue;
		}

		if (i == 2)
		{
			pCustomVertices[i].m_aRGB = bottomARGB;

			continue;
		}

		pCustomVertices[i].m_aRGB = aveColor;
	}
}

VOID CustomVertexEditor::SetObliqueToBottomLeftARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
{
	DWORD aveColor = 0;

	//α値を求める
	BYTE alphaValue[2] = { static_cast<BYTE>(topARGB >> 24) ,static_cast<BYTE>(bottomARGB >> 24) };
	aveColor += (((alphaValue[0] + alphaValue[1]) / 2) << 24);

	//r値を求める
	BYTE redValue[2] = { static_cast<BYTE>(topARGB >> 16) ,static_cast<BYTE>(bottomARGB >> 16) };
	aveColor += (((redValue[0] + redValue[1]) / 2) << 16);

	//g値を求める
	BYTE greenValue[2] = { static_cast<BYTE>(topARGB >> 8) ,static_cast<BYTE>(bottomARGB >> 8) };
	aveColor += (((greenValue[0] + greenValue[1]) / 2) << 8);

	//b値を求める
	BYTE blueValue[2] = { static_cast<BYTE>(topARGB) ,static_cast<BYTE>(bottomARGB) };
	aveColor += ((blueValue[0] + blueValue[1]) / 2);

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		if (i == 1)
		{
			pCustomVertices[i].m_aRGB = bottomARGB;

			continue;
		}

		if (i == 3)
		{
			pCustomVertices[i].m_aRGB = topARGB;

			continue;
		}

		pCustomVertices[i].m_aRGB = aveColor;
	}
}
