#ifndef SCENE_OBJ_H
#define SCENE_OBJ_H

#include <windows.h>

#include <d3dx9.h>

#include "../../../../IBaseWorking.h"
#include "../../../../../../GameLib/GameLib.h"
#include "Enum\OBJ_TYPE.h"

class Obj :public IBaseWorking
{
public:
	Obj(OBJ_TYPE objectType, FLOAT z) :m_rGameLib(GameLib::GetInstance()),
		m_WND_SIZE(m_rGameLib.GetWndSize()), m_OBJECT_TYPE(objectType), m_Z(z) {};
	~Obj() {};

	inline OBJ_TYPE GetObjectType() const
	{
		return m_OBJECT_TYPE;
	}

	inline FLOAT GetZ() const
	{
		return m_Z;
	}

protected:
	GameLib& m_rGameLib;

	const RectSize m_WND_SIZE = { 0,0 };

	const OBJ_TYPE m_OBJECT_TYPE = OT_TRANSPARENCY;
	const FLOAT m_Z = 1.0f;
};

#endif // !SCENE_OBJ_H
