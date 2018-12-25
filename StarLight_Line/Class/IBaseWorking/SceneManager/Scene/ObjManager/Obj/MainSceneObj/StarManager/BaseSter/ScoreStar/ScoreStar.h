#ifndef SCORE_STAR_H_
#define SCORE_STAR_H_

#include "../BaseStar.h"

class ScoreStar:public BaseStar
{
public:
	ScoreStar()
	{
		Init();
	}

	~ScoreStar()
	{
	}

	VOID Init();
	VOID Update();
	VOID Render();
};

#endif // !SCORE_STAR_H_
