#ifndef EFFECT_H
#define EFFECT_H

#include <windows.h>

#include <d3dx9.h>

#include <vector>

#include "Particle/Particle.h"

class Effect
{
public:
	Effect(size_t particlesNum, const TCHAR* pTexPath, INT activeCount) :m_COUNT_TO_ACTIVE_MAX(activeCount)
	{
		m_particles.resize(particlesNum);
		for (auto& i : m_particles) i = new Particle(pTexPath);
	}

	virtual ~Effect() 
	{
		for (auto i : m_particles) delete i;
		
		m_particles.clear();
		m_particles.shrink_to_fit();
	}

	virtual inline VOID Update() = 0;

	inline VOID Render()
	{
		m_rGameLib.AddtionBlendMode();

		for (INT i = 0; i < m_particles.size(); ++i)
		{
			if (i > m_activeLimit) continue;

			m_particles[i]->Render();
		}

		m_rGameLib.DefaultBlendMode();

		CountUpActiveLimit();
	}

	inline BOOL Ends() const
	{
		return m_ends;
	}

protected:
	VOID CountUpActiveLimit();

	inline VOID InitActivatedParticle()
	{
		for (INT i = 0; i < m_particles.size(); ++i)
		{
			if (i == m_activeLimit && m_countToActive == 0 && m_COUNT_TO_ACTIVE_MAX != 0)
			{
				Init(m_particles[i]);

				break;
			}
		}
	}

	virtual VOID Init(Particle* pParticle) {};

	GameLib& m_rGameLib = GameLib::GetInstance();

	std::vector<Particle*> m_particles;

	const INT m_COUNT_TO_ACTIVE_MAX = 0;
	INT m_countToActive = 0;
	INT m_activeLimit = 0;

	BOOL m_ends = FALSE;
};

#endif //! EFFECT_H
