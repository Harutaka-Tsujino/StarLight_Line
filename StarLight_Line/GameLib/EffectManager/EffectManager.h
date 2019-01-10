#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include <windows.h>

#include <d3dx9.h>

#include "../CustomVertexEditor/Data/CustomVertex.h"
#include "../FbxStorage/FbxRelated/FbxRelated.h"
#include "../FbxStorage/FbxRelated/FbxModel/FbxModel.h"
#include "../../../3DBoard/3DBoard.h"

class EffectManager
{
public:
	EffectManager(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};
	~EffectManager() {};

private:
private:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;
};

#endif //! EFFECT_MANAGER_H
