#ifndef PLAYER_EFFECT_H_
#define PLAYER_EFFECT_H_

#include <d3dx9.h>

#include "../../../Obj.h"

class PlayerEffect :public Obj
{
public:
	PlayerEffect() :Obj(OT_TRANSPARENCY, 0.0f)
	{
		Init();
	}

	~PlayerEffect()
	{

	}

	VOID Init();
	VOID Update();
	VOID Render();

};

#endif // !

