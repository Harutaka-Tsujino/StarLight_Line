#ifndef MAIN_TWO_PLAYER_SCENE_H_
#define MAIN_TWO_PLAYER_SCENE_H_

#include "../../Scene.h"
#include "../../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"
#include "../../ObjManager/Obj/2PSceneObjects/Main2PObj/Main2PObj.h"
#include "../../ObjManager/Obj/2PSceneObjects/Main2PObj/Player1/Player1.h"
#include "../../ObjManager/Obj/2PSceneObjects/Main2PObj/Player2/Player2.h"

class MainTwoPlayerScene :public Scene
{
public:
	MainTwoPlayerScene();

	~MainTwoPlayerScene()
	{
	}
};

#endif // !MAIN_TWO_PLAYER_SCENE_H_
