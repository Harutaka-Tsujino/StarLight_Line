#ifndef EFFECTS_H
#define EFFECTS_H

#include <windows.h>

#include <d3dx9.h>

#include "../Effect.h"
#include "../../../../Class/IBaseWorking/SceneManager/Scene/ObjManager/Obj/Obj.h"
#include "../../../DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

class GetScoreStarEffect :public Effect
{
public:
	GetScoreStarEffect(const D3DXVECTOR3& center) :Effect(13, _T("2DTextures/EffectTexture/Star.png"), 0), m_center(center)
	{
		if (m_COUNT_TO_ACTIVE_MAX != 0) return;

		for (auto i : m_particles) 
		{
			Init(i); 
		}
	}

	~GetScoreStarEffect() {};

	VOID Update();

protected:
	inline VOID Init(Particle* pParticle)
	{
		D3DXVECTOR2 halfScale = { 1.5f, 1.5f };

		pParticle->FormatShape(halfScale, 2.0f);
		pParticle->SetColor(0x0087CEFA);
		pParticle->FormatCenter(m_center, 20.0f);
		
		pParticle->ZeroLifeFrame();
		pParticle->ZeroVelocity();
		pParticle->FormatRadiationInitialVelocity(2.0f, 0.0f);
	}

	D3DXVECTOR3 m_center;
};

class GetClearStarEffect :public Effect
{
public:
	GetClearStarEffect(const D3DXVECTOR3& center) :Effect(40, _T("2DTextures/EffectTexture/Star.png"), 0), m_center(center)
	{
		if (m_COUNT_TO_ACTIVE_MAX != 0) return;

		for (auto i : m_particles) 
		{
			Init(i); 
		}
	}

	~GetClearStarEffect() {};

	VOID Update();

protected:
	inline VOID Init(Particle* pParticle)
	{
		D3DXVECTOR2 halfScale = { 1.5f, 1.5f };

		pParticle->FormatShape(halfScale, 2.0f);
		pParticle->SetColor(0x0098FB98);
		pParticle->FormatCenter(m_center, 20.0f);

		pParticle->ZeroLifeFrame();
		pParticle->ZeroVelocity();
		pParticle->FormatRadiationInitialVelocity(3.0f, 0.0f);
	}

	D3DXVECTOR3 m_center;
};

class GetDamageStarEffect :public Effect
{
public:
	GetDamageStarEffect(const D3DXVECTOR3& center) :Effect(25, _T("2DTextures/EffectTexture/Star.png"), 0), m_center(center)
	{
		if (m_COUNT_TO_ACTIVE_MAX != 0) return;

		for (auto i : m_particles) 
		{
			Init(i); 
		}
	}

	~GetDamageStarEffect() {};

	VOID Update();

protected:
	inline VOID Init(Particle* pParticle)
	{
		D3DXVECTOR2 halfScale = { 1.5f, 1.5f };

		pParticle->FormatShape(halfScale, 2.0f);
		pParticle->SetColor(0x00FFFFFF);
		pParticle->FormatCenter(m_center, 80.0f,10.0f);

		pParticle->ZeroLifeFrame();
		pParticle->ZeroVelocity();
		pParticle->FormatAbsorptionInitialVelocity(3.0f, 0.0f);
	}

	D3DXVECTOR3 m_center;
};

class MouseCursorEffect :public Effect
{
public:
	MouseCursorEffect() :Effect(60, _T("2DTextures/EffectTexture/Star.png"), 1)
	{
		if (m_COUNT_TO_ACTIVE_MAX != 0) return;

		for (auto i : m_particles)
		{
			Init(i);
		}
	}

	~MouseCursorEffect() {};

	VOID Update();

protected:
	VOID Init(Particle* pParticle)
	{
		D3DXVECTOR2 halfScale = { 1.5f, 1.5f };

		POINT cursorPos;
		m_rGameLib.CursorPos(&cursorPos);
		D3DXVECTOR3 center = { static_cast<FLOAT>(cursorPos.x), static_cast<FLOAT>(cursorPos.y), 0.0f };

		pParticle->FormatShape(halfScale, 2.0f);
		pParticle->SetColor(0x00DFFA20);
		pParticle->FormatCenter(center, 20.0f);

		pParticle->ZeroLifeFrame();
		pParticle->ZeroVelocity(); 
	}

	VOID InitCursor(Particle* pParticle)
	{
		D3DXVECTOR2 halfScale = { 5.5f, 5.5f };

		POINT cursorPos;
		m_rGameLib.CursorPos(&cursorPos);
		D3DXVECTOR3 center = { static_cast<FLOAT>(cursorPos.x), static_cast<FLOAT>(cursorPos.y), 0.0f };

		pParticle->FormatShape(halfScale, 0.0f);
		pParticle->SetColor(0xFFDFFA20);
		pParticle->FormatCenter(center, 0.0f);
	}
};

class FlowerFallingEffect :public Effect
{
public:
	FlowerFallingEffect() :Effect(30, nullptr, 0)
	{
		if (m_COUNT_TO_ACTIVE_MAX != 0) return;

		for (auto i : m_particles)
		{
			Init(i);
		}

		std::random_device randDevForSeed;
		m_randEngine.seed(randDevForSeed());
	}

	~FlowerFallingEffect() {}

	VOID Update();

private:
	VOID Init(Particle* pParticle)
	{
		D3DXVECTOR2 halfScale = { 3.5f, 3.5f };

		DWORD colors[2] = { 0xCAF8F8F8,0xCA87CEFA };

		pParticle->FormatShape(halfScale, 0.0f);
		pParticle->SetColor(colors[rand() % 2]);

		D3DXVECTOR3 center(static_cast<FLOAT>(rand() % 1280), static_cast<FLOAT>(-rand() % 1000), 0.0f);
		pParticle->FormatCenter(center, 0.0f);

		pParticle->ZeroLifeFrame();
		pParticle->ZeroVelocity();

		D3DXVECTOR2 gravity = { 0.0f , 3.0f };

		pParticle->Accelarate(gravity);
	}

	std::minstd_rand m_randEngine;
};

#endif //! EFFECTS_H
