#ifndef CLEAR_STAR_H_
#define CLEAR_STAT_H_

#include "../BaseStar.h"

class ClearStar:public BaseStar
{
public:
	ClearStar() 
	{
		Init();
	}

	~ClearStar() {}

	VOID Render();
};

#endif // !CLEAR_STAR_H_
