#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include <windows.h>

#include <vector>

#include <d3dx9.h>

#include "../../Class/Singleton/Singleton.h"
#include "Effect\Effect.h"
#include "Effect\Effects\Enum\EFFECT_ID.h"
#include "Effect\Effects\Effects.h"

class EffectManager :public Singleton<EffectManager>
{
public:
	friend class Singleton<EffectManager>;

	~EffectManager() 
	{
		AllDelete();
	}

	inline VOID CreateEffect(const D3DXVECTOR3& center, INT effectId)
	{
		switch (effectId)
		{
		case EI_SCORE:
			m_pEffects.push_back(static_cast<Effect*>(new GetScoreStarEffect(center)));

			break;

		case EI_CLEAR:
			m_pEffects.push_back(static_cast<Effect*>(new GetClearStarEffect(center)));

			break;

		case EI_DAMAGE:
			m_pEffects.push_back(static_cast<Effect*>(new GetDamageStarEffect(center)));

			break;

		case EI_FLOWER_FALLING:
			m_pEffects.push_back(static_cast<Effect*>(new FlowerFallingEffect()));

			break;

		default:
			break;
		}
	}

	inline VOID Update()
	{
		if (m_pEffects.size() <= 0) return;

		ReleaseEndEffects();

		for (auto i : m_pEffects)
		{
			i->Update();
		}
	}

	inline VOID Render()
	{
		if (m_pEffects.size() <= 0) return;

		for (auto i : m_pEffects)
		{
			i->Render();
		}
	}

	inline VOID AllDelete()
	{
		for (auto i : m_pEffects)
		{
			delete i;
		}

		m_pEffects.clear();
		m_pEffects.shrink_to_fit();
	}

private:
	EffectManager() 
	{
		m_pEffects.push_back(static_cast<Effect*>(new MouseCursorEffect()));
	}

	inline VOID ReleaseEndEffects()
	{
		if (m_pEffects.size() <= 0) return;

		for (INT i = static_cast<INT>(m_pEffects.size() - 1); i >= 0; --i)
		{
			if (m_pEffects[i]->Ends())
			{
				delete m_pEffects[i];

				std::vector<Effect*>::iterator thisIndexItr = m_pEffects.begin() + i;

				m_pEffects.erase(thisIndexItr);
			}
		}
	}

	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;

	std::vector<Effect*> m_pEffects;
};

#endif //! EFFECT_MANAGER_H
