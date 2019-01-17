#ifndef RESULT_TWO_PLAYER_SCENE_H_
#define RESULT_TWO_PLAYER_SCENE_H_

#include "../../Scene.h"
#include "../../ObjManager/Obj/2PSceneObjects/Result2PObj/Result2PObj.h"

class ResultTwoPlayerScene :public Scene
{
public:
	ResultTwoPlayerScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new ResultTwoPlayerBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new ResultTwoPlayerFrame()));
		m_pObjManager->Resister(static_cast<Obj*>(new ResultTwoPlayerStage()));
		m_pObjManager->Resister(static_cast<Obj*>(new ResultTwoPlayerScore()));
	}

	~ResultTwoPlayerScene()
	{
	}
};

#endif // !RESULT_TWO_PLAYER_SCENE_H_
