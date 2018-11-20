#ifndef SCENE_H
#define SCENE_H

#include <windows.h>

#include "../../IBaseWorking.h"
#include "ObjManager\ObjManager.h"

class Scene :public IBaseWorking
{
public:
	Scene()
	{
		m_pObjManager = new ObjManager();
	}

	~Scene()
	{
		delete m_pObjManager;
	}

private:
	ObjManager* m_pObjManager = nullptr;
};

#endif // !SCENE_H
