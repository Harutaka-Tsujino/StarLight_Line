#ifndef MAIN_SCENE_H_
#define MAIN_SCENE_H_

#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"
#include "../ObjManager/Obj/MainSceneObj/Player/Player.h"

class MainScene :public Scene
{
public:
	MainScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new MainBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new Player()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerLifeFrame()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerScoreFrame()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerClearStarObj()));
		m_pObjManager->Resister(static_cast<Obj*>(new StarManager()));
	}

	~MainScene() {};
};

#endif // !MAIN_SCENE_H_
