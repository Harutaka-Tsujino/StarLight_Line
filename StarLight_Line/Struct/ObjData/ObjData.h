/**
* @brief ���̂̏�ԍ\���̂̃w�b�_
* @author Harutaka-Tsujino
*/

#ifndef OBJ_DATA_H
#define OBJ_DATA_H

#include <windows.h>

#include <d3dx9.h>

/**
* @brief ���̂̏��
*/
struct ObjData
{
	D3DXVECTOR3 m_center	= { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_halfScale = { 0.0f,0.0f,0.0f };

	D3DXVECTOR3 m_deg = { 0.0f,0.0f,0.0f };	//! x y z���̏���

	DWORD m_aRGB = 0xFFFFFFFF;
};

#endif										//! OBJ_DATA_H
