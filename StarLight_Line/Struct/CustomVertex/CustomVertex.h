/**
* @brief ���_�f�[�^�\���̂̃w�b�_
* @author Harutaka-Tsujino
*/

#ifndef CUSTOM_VERTEX_H
#define CUSTOM_VERTEX_H

#include <windows.h>
#include <d3dx9.h>

/**
* @brief ���_�f�[�^
*/
struct CustomVertex
{
public:
	D3DXVECTOR3 m_pos;

	FLOAT m_rHW = 1.0f;			//! �d�݂̋t�� ��{1

	DWORD m_aRGB = 0xFFFFFFFF;

	D3DXVECTOR2 m_texUV;		//! �e�N�X�`���̍��W
};

#endif // !CUSTOM_VERTEX_H
