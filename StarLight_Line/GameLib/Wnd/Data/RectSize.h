/**
* @file RectSize.h
* @brief 平面上の値構造体のヘッダ
* @author Harutaka-Tsujino
*/

#ifndef RECT_SIZE_H
#define RECT_SIZE_H

#include <windows.h>

#include <d3dx9.h>

/**
* @brief 平面上で用いられるサイズなどの値
*/
struct RectSize
{
public:
	inline VOID TransD3DXVECTOR3(D3DXVECTOR3* pVec3_in) const
	{
		*pVec3_in = { static_cast<FLOAT>(m_x), static_cast<FLOAT>(m_y), 0.0f };
	}

	INT m_x = 0;
	INT m_y = 0;
};

#endif //! RECT_SIZE_H
