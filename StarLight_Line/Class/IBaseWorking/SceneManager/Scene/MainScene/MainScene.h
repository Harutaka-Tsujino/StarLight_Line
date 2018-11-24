#ifndef MAIN_SCENE_H_
#define MAIN_SCENE_H_

#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"

//オブジェクトの登録だけ
class MainScene :public Scene
{
public:
	MainScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new MainBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new StarManager()));
	}

	~MainScene() {};
};

#endif // !MAIN_SCENE_H_