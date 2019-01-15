#ifndef MAIN_TWO_PLAYER_SCENE_H_
#define MAIN_TWO_PLAYER_SCENE_H_

#include "../../Scene.h"
#include "../../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"

class MainTwoPlayerScene :public Scene
{
public:
	MainTwoPlayerScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new MainBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new MainLine()));
		m_pObjManager->Resister(static_cast<Obj*>(new StarManager()));
	}

	~MainTwoPlayerScene()
	{
	}
};

#endif // !MAIN_TWO_PLAYER_SCENE_H_
