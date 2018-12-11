#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../ObjManager/Obj/MainSceneObj/MainSceneObject.h"
#include "../ObjManager/Obj/MainSceneObj/StarManager/StarManager.h"
#include "../ObjManager/Obj/ResultSceneObj/ResultSceneObj.h"

class ResultScene :public Scene
{
public:
	ResultScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new ResultSceneBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new ResultSceneResult()));
	}

	~ResultScene() {};
};

#endif //! RESULT_SCENE_H
