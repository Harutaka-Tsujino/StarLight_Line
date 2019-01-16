#ifndef MAIN_TWO_PLAYER_SCENE_H_
#define MAIN_TWO_PLAYER_SCENE_H_

#include "../../Scene.h"
#include "../../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"
#include "../../ObjManager/Obj/2PSceneObjects/Main2PObj/Main2PObj.h"
#include "../../ObjManager/Obj/2PSceneObjects/Main2PObj/Player1/Player1.h"

class MainTwoPlayerScene :public Scene
{
public:
	MainTwoPlayerScene()
	{
		GameLib& rGameLib = GameLib::GetInstance();

		rGameLib.SetCameraPos(0.0f, -2.15f, -1.0f);
		rGameLib.SetCameraTransform();

		m_pObjManager->Resister(static_cast<Obj*>(new MainBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new MainLine()));
		m_pObjManager->Resister(static_cast<Obj*>(new ScoreFrameforTwoPlayer()));
		m_pObjManager->Resister(static_cast<Obj*>(new PlayerOne()));
		m_pObjManager->Resister(static_cast<Obj*>(new StarManager()));
	}

	~MainTwoPlayerScene()
	{
	}
};

#endif // !MAIN_TWO_PLAYER_SCENE_H_
