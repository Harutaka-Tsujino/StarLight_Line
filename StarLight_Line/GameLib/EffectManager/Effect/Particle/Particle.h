#ifndef PARTICLE_H
#define PARTICLE_H

#include <windows.h>

#include <d3dx9.h>

#include "../../../../Class/IBaseWorking/SceneManager/Scene/ObjManager/Obj/Obj.h"
#include "../../../DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"
#include "Behavior/Behavior.h"
#include "Shape/Shape.h"

class Particle
{
public:
	Particle(const TCHAR* pTexPath) :m_pTexName(pTexPath)
	{
		m_rGameLib.CreateTex(m_pTexName, m_pTexName);
	}

	virtual ~Particle() {};

	/*
	* 初期化関数群 初めに1度しか呼んではいけない
	*/
	inline VOID FormatShape(const D3DXVECTOR2& minScale, FLOAT additionalScaleDifferenceMulti = 0.0f)
	{
		Shape.Format(&m_objData, minScale, additionalScaleDifferenceMulti);
	}

	inline VOID FormatCenter(const D3DXVECTOR3& center, FLOAT centerDifferenceX, FLOAT centerDifferenceY)
	{
		Behavior.FormatCenter(&m_objData, center, centerDifferenceX, centerDifferenceY);
	}

	inline VOID FormatCenter(const D3DXVECTOR3& center, FLOAT centerDifference = 0.0f)
	{
		Behavior.FormatCenter(&m_objData, center, centerDifference);
	}

	inline VOID FormatInitialVelocity(FLOAT initialSpeed, FLOAT direction_deg, FLOAT directionDifference_deg = 0.0f)
	{
		Behavior.FormatInitialVelocity(initialSpeed, direction_deg, directionDifference_deg);
	}

	inline VOID FormatRadiationInitialVelocity(FLOAT initialSpeed, FLOAT directionDifference_deg = 0.0f)
	{
		Behavior.FormatRadiationInitialVelocity(m_objData, initialSpeed, directionDifference_deg);
	}

	inline VOID FormatAbsorptionInitialVelocity(FLOAT initialSpeed, FLOAT directionDifference_deg = 0.0f)
	{
		Behavior.FormatAbsorptionInitialVelocity(m_objData, initialSpeed, directionDifference_deg);
	}

	/*
	* 動作制御関数群 毎フレーム呼ぶ必要がある物もある
	*/
	inline VOID Accelarate(FLOAT speed, D3DXVECTOR2 directionVector)
	{
		Behavior.Accelarate(speed, directionVector);
	}

	inline VOID Accelarate(D3DXVECTOR2 velocity)
	{
		Behavior.Accelarate(velocity);
	}

	inline VOID ZeroVelocity()
	{
		Behavior.ZeroVelocity();
	}

	inline VOID Circulate(const D3DXVECTOR3& rotationBasePos, FLOAT minRotate_deg, FLOAT differenceAdditionalRotate_deg = 0.0f)
	{
		Behavior.Circulate(&m_objData, rotationBasePos, minRotate_deg, differenceAdditionalRotate_deg);
	}

	virtual inline VOID Update()
	{
		Behavior.CalcCenter(&m_objData);
	}

	virtual inline VOID Render()
	{
		CreateAndRenderRect();
	}

protected:
	VOID CreateAndRenderRect()
	{
		CustomVertex customVertex[4];

		m_rGameLib.CreateRect(customVertex, m_objData);
		m_rGameLib.Render(customVertex, m_rGameLib.GetTex(m_pTexName));
	}

	GameLib& m_rGameLib = GameLib::GetInstance();

	ObjData m_objData;

	Behavior Behavior;
	Shape Shape;

	const TCHAR* m_pTexName = nullptr;
};

#endif //! PARTICLE_H
