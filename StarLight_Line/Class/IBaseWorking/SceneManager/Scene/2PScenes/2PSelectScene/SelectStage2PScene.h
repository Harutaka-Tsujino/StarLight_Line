#ifndef STAGE_SELECT_TWO_PLAYER_SCENE_H_
#define STAGE_SELECT_TWO_PLAYER_SCENE_H_

#include <Windows.h>

#include "../../Scene.h"
#include "../../ObjManager/Obj/TitleSceneObj/TitleSceneObj.h"
#include "../../ObjManager/Obj/2PSceneObjects/StageSelect2PObj/StageSelect2PObj.h"

class StageSelectTwoPlayerScene :public Scene
{
public:
	StageSelectTwoPlayerScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new StageSelectTwoPlayerBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleSmallStarEffect()));
		m_pObjManager->Resister(static_cast<Obj*>(new StageSelectTwoPlayerSceneStages()));
	}

	~StageSelectTwoPlayerScene()
	{

	}
};

#endif // !STAGE_SELECT_TWO_PLAYER_SCENE_H_
