#ifndef END_SCENE_H
#define END_SCENE_H

#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../ObjManager/Obj/EndSceneObj/EndSceneObj.h"

class EndScene :public Scene
{
public:
	EndScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new EndSceneBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new EndSceneEiwi()));
	}

	~EndScene() {};
};

#endif // !END_SCENE_H
