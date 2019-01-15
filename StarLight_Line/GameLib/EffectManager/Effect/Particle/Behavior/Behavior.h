/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <windows.h>
#include <math.h>

# include <random>

#include <d3dx9.h>

#include "../../../../GameLib.h"
#include "../../../../DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

class Behavior
{
public:
	Behavior() 
	{
		std::random_device randDevForSeed;
		m_randEngine.seed(randDevForSeed());
	}

	~Behavior() {};

	/*
	* 初期化関数群 初めに1度しか呼んではいけない
	*/
	//inline VOID FormatCenter(ObjData* pObjData, const D3DXVECTOR3& center, FLOAT centerDifferenceX, FLOAT centerDifferenceY)
	//{
	//	std::uniform_real_distribution<FLOAT> centerXRand(-centerDifferenceX, centerDifferenceX);
	//	std::uniform_real_distribution<FLOAT> centerYRand(-centerDifferenceY, centerDifferenceY);
	//	
	//	pObjData->m_center = m_baseCenter = center;
	//	pObjData->m_center.x += centerXRand(m_randEngine);
	//	pObjData->m_center.y += centerYRand(m_randEngine);
	//}

	inline VOID FormatCenter(ObjData* pObjData, const D3DXVECTOR3& center, FLOAT centerDifference)
	{
		std::uniform_real_distribution<FLOAT> centerRand(-centerDifference, centerDifference);
		std::uniform_real_distribution<FLOAT> radRand(0.0f, 2.0f * D3DX_PI);

		D3DXVECTOR3 centerDifferenceVec = { centerRand(m_randEngine), 0.0f, pObjData->m_center.z };

		RotateVec3(&centerDifferenceVec, radRand(m_randEngine));

		pObjData->m_center = m_baseCenter = center;
		pObjData->m_center += centerDifferenceVec;
	}

	inline VOID FormatCenter(ObjData* pObjData, const D3DXVECTOR3& center, FLOAT minLengthToCenter, FLOAT centerDifference)
	{
		std::uniform_real_distribution<FLOAT> centerRand(minLengthToCenter, minLengthToCenter + centerDifference);
		std::uniform_real_distribution<FLOAT> radRand(0.0f, 2.0f * D3DX_PI);

		D3DXVECTOR3 centerDifferenceVec = { centerRand(m_randEngine), 0.0f, pObjData->m_center.z };

		RotateVec3(&centerDifferenceVec, radRand(m_randEngine));

		pObjData->m_center = m_baseCenter = center;
		pObjData->m_center += centerDifferenceVec;
	}

	inline VOID FormatInitialVelocity(FLOAT initialSpeed, FLOAT direction_deg, FLOAT directionDifference_deg = 0.0f)
	{
		std::uniform_real_distribution<FLOAT> degRand(-directionDifference_deg, directionDifference_deg);

		D3DXMATRIX rotateMatrix;
		D3DXVECTOR2 initialSpeedForRotate = { initialSpeed, 0.0f };
		D3DXMatrixRotationZ(&rotateMatrix, -D3DXToRadian(direction_deg + degRand(m_randEngine)));
		D3DXVec2TransformCoord(&m_velocity, &initialSpeedForRotate, &rotateMatrix);
	}

	inline VOID FormatRadiationInitialVelocity(const ObjData& ObjData, FLOAT initialSpeed, FLOAT directionDifference_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = ObjData.m_center;
		vectorBaseToCurrentPos -= m_baseCenter;

		FormatInitialVelocity(initialSpeed, CalcDegreeAgainstRightVector(vectorBaseToCurrentPos), directionDifference_deg);
	}

	inline VOID FormatAbsorptionInitialVelocity(const ObjData& ObjData, FLOAT initialSpeed, FLOAT directionDifference_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = m_baseCenter;
		vectorBaseToCurrentPos -= ObjData.m_center;

		FormatInitialVelocity(initialSpeed, CalcDegreeAgainstRightVector(vectorBaseToCurrentPos), directionDifference_deg);
	}

	/*
	* 動作制御関数群 毎フレーム呼ぶ必要がある物もある
	*/
	inline VOID Accelarate(FLOAT speed, D3DXVECTOR2 directionVector)
	{
		D3DXVECTOR2 unitDirectionVector;
		D3DXVec2Normalize(&unitDirectionVector, &directionVector);

		D3DXVECTOR2 velocity = speed * unitDirectionVector;
		m_velocity += velocity;
	}

	inline VOID Accelarate(D3DXVECTOR2 velocity)
	{
		m_velocity += velocity;
	}

	inline VOID ZeroVelocity()
	{
		ZeroMemory(&m_velocity, sizeof(D3DXVECTOR2));
	}

	inline VOID CalcCenter(ObjData* pObjData)
	{
		pObjData->m_center.x += m_velocity.x;
		pObjData->m_center.y += m_velocity.y;
	}

	inline VOID Circulate(ObjData* pObjData, const D3DXVECTOR3& rotationBasePos, FLOAT minRotate_deg, FLOAT differenceAdditionalRotate_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = pObjData->m_center - rotationBasePos;

		std::uniform_real_distribution<FLOAT> degRand(minRotate_deg, minRotate_deg + differenceAdditionalRotate_deg);

		D3DXMATRIX rotateMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, -D3DXToRadian(degRand(m_randEngine)));
		D3DXVec3TransformCoord(&vectorBaseToCurrentPos, &vectorBaseToCurrentPos, &rotateMatrix);
		
		pObjData->m_center = vectorBaseToCurrentPos + rotationBasePos;
	}

	inline VOID Circulate(ObjData* pObjData, FLOAT minRotate_deg, FLOAT differenceAdditionalRotate_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = pObjData->m_center - m_baseCenter;

		std::uniform_real_distribution<FLOAT> degRand(minRotate_deg, minRotate_deg + differenceAdditionalRotate_deg);

		D3DXMATRIX rotateMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, -D3DXToRadian(degRand(m_randEngine)));
		D3DXVec3TransformCoord(&vectorBaseToCurrentPos, &vectorBaseToCurrentPos, &rotateMatrix);

		pObjData->m_center = vectorBaseToCurrentPos + m_baseCenter;
	}

	/*
	* 処理をループさせるための関数
	*/
	inline BOOL IsOutSide(const ObjData& objData, const D3DXVECTOR3& additionalRangeMin, FLOAT differenceAdditionalRangeMulti = 0.0f)
	{
		std::uniform_real_distribution<FLOAT> additionalRangMultiRand(1.0f, 1.0f + differenceAdditionalRangeMulti);

		FLOAT additionalRangMulti = additionalRangMultiRand(m_randEngine);
		D3DXVECTOR3 additonalRange = { additionalRangMulti * additionalRangeMin.x, additionalRangMulti * additionalRangeMin.y, objData.m_center.z };

		D3DXVECTOR3 radiusVec = objData.m_center - m_baseCenter;
		FLOAT radius = D3DXVec3Length(&radiusVec);

		if (radius > D3DXVec3Length(&additonalRange)) return TRUE;

		return FALSE;
	}

	inline VOID SetAlpha(ObjData* pObjData , BYTE alpha)
	{
		pObjData->m_aRGB &= 0x00FFFFFF;
		pObjData->m_aRGB += (alpha << 24);
	}

	inline VOID FeedIn(ObjData* pObjData, INT startFrame, INT takesFrame, INT lifeTime)
	{
		if (lifeTime < startFrame || lifeTime > startFrame + takesFrame) return;

		SetAlpha(pObjData, static_cast<BYTE>(255.0f * (lifeTime - startFrame) / takesFrame));
	}

	inline VOID FeedOut(ObjData* pObjData, INT startFrame, INT takesFrame, INT lifeTime)
	{
		if (lifeTime < startFrame || lifeTime > startFrame + takesFrame) return;

		SetAlpha(pObjData, static_cast<BYTE>(255.0f * (1.0f - (lifeTime - startFrame) / static_cast<FLOAT>(takesFrame))));
	}

private:
	inline FLOAT CalcDegreeAgainstRightVector(const D3DXVECTOR3& vectorPos) const
	{
		FLOAT radian = 0.0f;
		FLOAT vectorBaseToCurrentPosLength = D3DXVec3Length(&vectorPos);

		if (vectorBaseToCurrentPosLength != 0.0f)
		{
			const D3DXVECTOR3 BASE_VECTOR = { 1.0f, 0.0f, m_baseCenter.z };

			FLOAT cos = D3DXVec3Dot(&BASE_VECTOR, &vectorPos) / vectorBaseToCurrentPosLength;
			radian = acos(cos) * ((vectorPos.y >= 0.0f) ? -1.0f : +1.0f);
		}

		return D3DXToDegree(radian);
	}

	inline VOID RotateVec3(D3DXVECTOR3* pVec3, FLOAT rad)
	{
		D3DXMATRIX rotateMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, rad);
		D3DXVec3TransformCoord(pVec3, pVec3, &rotateMatrix);
	}

	std::minstd_rand m_randEngine;

	D3DXVECTOR2 m_velocity = { 0.0f, 0.0f };

	D3DXVECTOR3 m_baseCenter = { 0.0f, 0.0f, 0.0f };
};

#endif //! BEHAVIOR_H
