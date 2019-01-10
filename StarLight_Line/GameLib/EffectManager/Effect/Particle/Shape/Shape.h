#ifndef SHAPE_H
#define SHAPE_H

#include <windows.h>

# include <random>

#include <d3dx9.h>

#include "../../../../GameLib.h"
#include "../../../../DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

class Shape
{
public:
	Shape() {};
	~Shape() {};

	inline VOID Format(ObjData* pObjData, const D3DXVECTOR2& minScale, FLOAT additionalScaleDifferenceMulti = 0.0f) const
	{
		std::random_device randDev;
		std::minstd_rand randEngine(randDev());
		
		FLOAT scaleDifferenceMulti = 1.0f + additionalScaleDifferenceMulti;
		std::uniform_real_distribution<FLOAT> scaleMultiRand(1.0f, scaleDifferenceMulti);

		FLOAT scaleMulti = minScale.x * scaleMultiRand(randEngine);

		pObjData->m_halfScale = { minScale.x * scaleMulti, minScale.y * scaleMulti, 0.0f };
	}
};

#endif //! SHAPE_H
