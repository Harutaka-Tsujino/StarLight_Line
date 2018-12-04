#ifndef PLAYER_HP_H_
#define PLAYER_HP_H_

#include "../../../../../../../../../GameLib/GameLib.h"
#include "../../../Obj.h"

class PlayerHP:public Obj
{
public:
	PlayerHP() :Obj(OT_UI, 0.0f)
	{
		Init();
	}

	~PlayerHP()
	{
		
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	INT m_HP;
};

#endif // !PLAYER_HP_H_
