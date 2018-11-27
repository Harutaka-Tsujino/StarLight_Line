#ifndef MAIN_SCENE_OBJECT_H_
#define MAIN_SCENE_OBJECT_H_

#include <Windows.h>

#include "../Obj.h"
#include "../../../../../../../GameLib/GameLib.h"

class MainBack :public Obj
{
public:
	MainBack() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~MainBack() 
	{
		m_rGameLib.ReleaseTex();
	}

	VOID Init();
	VOID Update() {};
	VOID Render();
};

#endif // !MAIN_SCENE_OBJECT_H_