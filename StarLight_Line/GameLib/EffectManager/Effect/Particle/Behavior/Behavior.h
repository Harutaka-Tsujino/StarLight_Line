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
	inline VOID FormatCenter(ObjData* pObjData, const D3DXVECTOR3& center, FLOAT centerDifferenceX, FLOAT centerDifferenceY)
	{
		std::uniform_real_distribution<FLOAT> centerXRand(-centerDifferenceX, centerDifferenceX);
		std::uniform_real_distribution<FLOAT> centerYRand(-centerDifferenceY, centerDifferenceY);
		
		pObjData->m_center = m_baseCenter = center;
		pObjData->m_center.x += centerXRand(m_randEngine);
		pObjData->m_center.y += centerYRand(m_randEngine);
	}

	inline VOID FormatCenter(ObjData* pObjData, const D3DXVECTOR3& center, FLOAT centerDifference = 0.0f)
	{
		std::random_device randDev;
		std::minstd_rand m_randEngine(randDev());

		std::uniform_real_distribution<FLOAT> centerRand(-centerDifference, centerDifference);

		pObjData->m_center = m_baseCenter = center;
		pObjData->m_center.x += centerRand(m_randEngine);
		pObjData->m_center.y += centerRand(m_randEngine);
	}

	inline VOID FormatInitialVelocity(FLOAT initialSpeed, FLOAT direction_deg, FLOAT directionDifference_deg = 0.0f)
	{
		std::random_device randDev;
		std::minstd_rand m_randEngine(randDev());
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

	inline VOID CalcCenter(ObjData* pObjData) const
	{
		pObjData->m_center.x += m_velocity.x;
		pObjData->m_center.y += m_velocity.y;
	}

	inline VOID Circulate(ObjData* pObjData, const D3DXVECTOR3& rotationBasePos, FLOAT minRotate_deg, FLOAT differenceAdditionalRotate_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = pObjData->m_center - rotationBasePos;
		D3DXVECTOR3 centerForRotate = vectorBaseToCurrentPos;

		
		std::uniform_real_distribution<FLOAT> degRand(minRotate_deg, minRotate_deg + differenceAdditionalRotate_deg);

		D3DXMATRIX rotateMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, -D3DXToRadian(degRand(m_randEngine)));
		D3DXVec3TransformCoord(&centerForRotate, &centerForRotate, &rotateMatrix);
		
		pObjData->m_center += centerForRotate;
	}

private:
	inline FLOAT CalcDegreeAgainstRightVector(const D3DXVECTOR3& vectorPos) const
	{
		FLOAT radius = 0.0f;
		FLOAT vectorBaseToCurrentPosLength = D3DXVec3Length(&vectorPos);

		if (vectorBaseToCurrentPosLength != 0.0f)
		{
			const D3DXVECTOR3 BASE_VECTOR = { 1.0f, 0.0f, 0.0f };

			FLOAT cos = D3DXVec3Dot(&BASE_VECTOR, &vectorPos) / vectorBaseToCurrentPosLength;
			radius = acos(cos) * ((vectorPos.y >= 0.0f) ? +1.0f : -1.0f);
		}

		return D3DXToDegree(radius);
	}

	std::minstd_rand m_randEngine;

	D3DXVECTOR2 m_velocity = { 0.0f, 0.0f };

	D3DXVECTOR3 m_baseCenter = { 0.0f, 0.0f, 0.0f };
};

#endif //! BEHAVIOR_H
