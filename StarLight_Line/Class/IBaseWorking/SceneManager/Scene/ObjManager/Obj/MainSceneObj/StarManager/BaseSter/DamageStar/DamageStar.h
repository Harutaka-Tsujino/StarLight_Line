#ifndef DAMAGE_STAR_H_
#define DAMAGE_STAR_H_

#include "../BaseStar.h"

class DamageStar :public BaseStar
{
public:
	DamageStar()
	{
		Init();
	}

	~DamageStar();

	VOID Render();
};

#endif // !DAMAGE_STAR_H_