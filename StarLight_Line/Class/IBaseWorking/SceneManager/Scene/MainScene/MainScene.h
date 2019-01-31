#ifndef MAIN_SCENE_H_
#define MAIN_SCENE_H_

#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"
#include "../ObjManager/Obj/MainSceneObj/Player/Player.h"
#include "../ObjManager/Obj/TitleSceneObj/TitleSceneObj.h"
#include "../ObjManager/Obj/MainSceneObj/Player/PlayerEffect/PlayerEffect.h"
#include "../ObjManager/Obj/MainSceneObj/StageProgress/StageProgress.h"

class MainScene :public Scene
{
public:
	MainScene()
	{
		GameLib& rGameLib = GameLib::GetInstance();

		rGameLib.SetCameraPos(0.0f, -2.15f, -1.0f);
		rGameLib.SetCameraTransform();

		m_pObjManager->Resister(static_cast<Obj*>(new MainBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleSmallStarEffect()));
		m_pObjManager->Resister(static_cast<Obj*>(new MainLine()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerLifeFrame()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerScoreFrame()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerClearStarObj()));
		m_pObjManager->Resister(static_cast<Obj*>(new StageProgress()));
	}

	~MainScene() {};
};

#endif // !MAIN_SCENE_H_
