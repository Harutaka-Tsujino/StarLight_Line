#ifndef TUTORIAL_SCENE_H
#define TUTORIAL_SCENE_H

#include <windows.h>

#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"
#include "../ObjManager/Obj/MainSceneObj/Player/Player.h"
#include "../ObjManager/Obj/TitleSceneObj/TitleSceneObj.h"
#include "../ObjManager/Obj/MainSceneObj/Player/PlayerEffect/PlayerEffect.h"
#include "../ObjManager/Obj/TutorialSceneObj/TutorialSceneObj.h"

class TutorialScene :public Scene
{
public:
	TutorialScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new MainBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleSmallStarEffect()));
		m_pObjManager->Resister(static_cast<Obj*>(new MainLine()));
		m_pObjManager->Resister(static_cast<Obj*>(new Player()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerLifeFrame()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerScoreFrame()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerClearStarObj()));
		m_pObjManager->Resister(static_cast<Obj*>(new TutorialManager()));
	}

	~TutorialScene() {};
};

#endif //! TUTORIAL_SCENE_H

