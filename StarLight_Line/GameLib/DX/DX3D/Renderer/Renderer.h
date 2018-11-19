/**
* @brief �`����s���N���X�̃w�b�_
* @author Harutaka Tsujino
*/
#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>

#include <d3dx9.h>

#include "../../../../Struct/CustomVertex/CustomVertex.h"

/**
* @class Renderer
* @brief �`����s��
*/
class Renderer
{
public:
	Renderer(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};
	~Renderer() {};

	/**
	* @brief FBX�̕`����s��
	* @param rFBXModel FBX�̃N���X ���f����ǂݍ��񂾌�łȂ��Ƃ����Ȃ�
	* @param rMatWorld �g���]�ړ��s����܂Ƃ߂��s��
	* @param pTexture ���f���ɒ���t����e�N�X�`���̃|�C���^ �f�t�H���g�ő��݂��Ă���ꍇ��nullptr
	* @detail�@rMatWorld��SetTransform,pTexture���Z�b�g������ FbxRelated�̃��\�b�h��p���`�悷��
	*/
	//inline VOID Render(const FbxRelated& rFBXModel
	//, const D3DXMATRIX& pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const;

	/**
	* @brief 2D�̕`����s��
	* @param pCustomVertices �`�悷���`�̒��_�f�[�^�̐擪�|�C���^
	* @param pTexture �|���S���ɒ���t����e�N�X�`���̃|�C���^
	* @detail pTexture���Z�b�g������ADrawPrimitiveUp��p���`�悷��
	*/
	inline VOID Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_rpDX3D_DEV->SetFVF(
						D3DFVF_XYZRHW |
						D3DFVF_DIFFUSE |
						D3DFVF_TEX1);

		m_rpDX3D_DEV->SetTexture(0, pTexture);

		m_rpDX3D_DEV->DrawPrimitiveUP(
						D3DPT_TRIANGLEFAN,
						2,
						pCustomVertices, sizeof(CustomVertex));
	}

public:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;
};

#endif // !RENDERER_H
