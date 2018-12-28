#ifndef PLAYER_HP_H_
#define PLAYER_HP_H_

#include <vector>

#include "../../../Obj.h"
#include "../../../../../../../../../GameLib/GameLib.h"
#include "../../GameCollision/GameCollision.h"
#include "../../Enum/STAR_TYPE.h"

class PlayerHP :public Obj
{
public:
	PlayerHP() :Obj(OT_UI, 0.0f), m_rGameCollision(GameCollision::GetInstance())
	{
		static BOOL inits = FALSE;

		if (!inits)
		{
			m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/Stage/HitWhiteStar.mp3"), _T("HitWhite"));
			m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/Stage/HitLethal.mp3"), _T("HitLethal"));

			inits = TRUE;
		}

		Init();
	}
	
	~PlayerHP()
	{
		ReleaseVertex();
		m_rGameLib.ReleaseTex();
	}

	VOID Init();
	VOID Update();
	VOID Render();

	VOID CreateVertex();
	VOID ReleaseVertex();
	INT GetHP() { return m_HP; }

	inline INT GetAdditionalFlashMulti() { return m_AdditionalFlashMulti; }

private:
	VOID CutUV(TexUV* UV);

	std::vector<CustomVertex*> m_HpRect;

	INT m_HP;

	INT m_AdditionalFlashMulti = 0;

	GameCollision& m_rGameCollision;
};

#endif // !PLAYER_HP_H_
