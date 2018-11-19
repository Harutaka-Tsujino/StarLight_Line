/**
* @brief �ėp�N���X��Facade�̃w�b�_
* @author Harutaka-Tsujino
*/

#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <Windows.h>

#include <d3dx9.h>

#include "../Class/Singleton/Singleton.h"
#include "Wnd\Wnd.h"
#include "DX\DX.h"
#include "../Struct/CustomVertex/CustomVertex.h"

/**
* @brief �ėp�N���X��Facade,�E�B���h�E������DX�֌W�̏��������s��
*/
class GameLib :public Singleton<GameLib>
{
public:
	friend class Singleton<GameLib>;

	~GameLib()
	{
		delete m_pDX;
		delete m_pWnd;
	};

	/**
	* @brief �E�B���h�E�𐶐���DX�֌W������������,��ԏ��߂ɂ�����Ă�
	* @param hInst �C���X�^���X�̃n���h��
	* @param pAppName �A�v���P�[�V�����̖��O�̃|�C���^
	*/
	inline static VOID Create(const HINSTANCE hInst, const TCHAR* pAppName)
	{
		if (m_pWnd) return;
		if (m_pDX) return;

		m_pWnd = new Wnd(hInst, pAppName);

		m_pDX = new DX(m_pWnd->GetHWND(), m_pWnd->GetWndSize());

		GetInstance();
	}

	/**
	* @brief ���b�Z�[�W���[�v���쐬�������ŗ^����ꂽ�֐���60fps�ŉ�
	* @param ���b�Z�[�W���[�v�ŉ񂷊֐��̃|�C���^
	*/
	VOID RunFunc(VOID(*pMainFunc)());

	inline SurfaceVal GetWndSize() const
	{
		return m_pWnd->GetWndSize();
	}

	inline VOID ToggleWndMode()								//�g�p��DX3DDev�����X�g����\��������
	{
		m_pDX->ToggleWndMode();
	}

	inline VOID DefaultBlendMode() const					//�ʏ퍇��
	{
		m_pDX->DefaultBlendMode();
	}

	inline VOID AddtionBlendMode() const					//���Z����
	{
		m_pDX->AddtionBlendMode();
	}

	inline VOID DefaultColorBlending() const				//�E�B���h�E���[�h��؂�ւ������ɂ͍Đݒ肷��K�v������
	{
		m_pDX->DefaultColorBlending();
	}

	inline VOID SetLight(const D3DLIGHT9& rLight, DWORD index) const
	{
		m_pDX->SetLight(rLight, index);
	}

	inline VOID OnLight(DWORD index) const
	{
		m_pDX->OnLight(index);
	}

	inline VOID OffLight(DWORD index) const
	{
		m_pDX->OffLight(index);
	}

	inline VOID EnableLighting() const
	{
		m_pDX->EnableLighting();
	}

	inline VOID DisableLighting() const
	{
		m_pDX->DisableLighting();
	}

	inline VOID ChangeAmbientIntensity(DWORD aRGB) const
	{
		m_pDX->ChangeAmbientIntensity(aRGB);
	}

	inline VOID EnableSpecular() const
	{
		m_pDX->EnableSpecular();
	}

	inline VOID DisaableSpecular() const
	{
		m_pDX->DisaableSpecular();
	}

	inline VOID DefaultLighting() const						//�E�B���h�E���[�h��؂�ւ������ɂ͍Đݒ肷��K�v������
	{
		m_pDX->DefaultLighting();
	}

	inline VOID CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath)
	{
		m_pDX->CreateTex(pTexKey, pTexPath);
	}

	inline VOID ReleaseTex()
	{
		m_pDX->ReleaseTex();
	}

	inline const LPDIRECT3DTEXTURE9 GetTex(const TCHAR* pTexKey)
	{
		return m_pDX->GetTex(pTexKey);
	}

	inline VOID GetCameraPos(D3DXVECTOR3* pCameraPos) const
	{
		m_pDX->GetCameraPos(pCameraPos);
	}

	inline VOID SetCameraPos(FLOAT x, FLOAT y, FLOAT z)
	{
		m_pDX->SetCameraPos(x, y, z);
	}

	inline VOID SetCameraPos(const D3DXVECTOR3& rCameraPos)
	{
		m_pDX->SetCameraPos(rCameraPos);
	}

	inline VOID GetCameraEyePt(D3DXVECTOR3* pEyePoint) const
	{
		m_pDX->GetCameraPos(pEyePoint);
	}

	inline VOID SetCameraEyePt(FLOAT x, FLOAT y, FLOAT z)
	{
		m_pDX->SetCameraEyePt(x, y, z);
	}

	inline VOID SetCameraEyePt(const D3DXVECTOR3& rEyePt)
	{
		m_pDX->SetCameraEyePt(rEyePt);
	}

	inline VOID GetView(D3DXMATRIX* pView) const
	{
		m_pDX->GetView(pView);
	}

	inline VOID GetProj(D3DXMATRIX* pProj) const
	{
		m_pDX->GetProj(pProj);
	}

	VOID SetCameraTransform()
	{
		m_pDX->SetCameraTransform();
	}

	inline VOID TransBillBoard(D3DXMATRIX* pWorld) const
	{
		m_pDX->TransBillBoard(pWorld);
	}

	inline VOID RotateRectXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3& rDeg, const D3DXVECTOR3& rRelativeRotateCenter) const
	{
		m_pDX->RotateRectXYZ(pCustomVertices, rDeg, rRelativeRotateCenter);
	}

	inline VOID RotateRectX(CustomVertex* pCustomVertices, FLOAT deg, const D3DXVECTOR3& rRelativeRotateCenter) const
	{
		m_pDX->RotateRectX(pCustomVertices, deg, rRelativeRotateCenter);
	}

	inline VOID RotateRectY(CustomVertex* pCustomVertices, FLOAT deg, const D3DXVECTOR3& rRelativeRotateCenter) const
	{
		m_pDX->RotateRectY(pCustomVertices, deg, rRelativeRotateCenter);
	}

	inline VOID RotateRectZ(CustomVertex* pCustomVertices, FLOAT deg, const D3DXVECTOR3& rRelativeRotateCenter) const
	{
		m_pDX->RotateRectZ(pCustomVertices, deg, rRelativeRotateCenter);
	}

	inline VOID RescaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR2& rScaleRate) const
	{
		m_pDX->RescaleRect(pCustomVertices, rScaleRate);
	}

	inline VOID MoveRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& rMovement) const
	{
		m_pDX->MoveRect(pCustomVertices, rMovement);
	}

	inline VOID LocaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& rPos) const
	{
		m_pDX->LocaleRect(pCustomVertices, rPos);
	}

	inline VOID SetRectTexUV(CustomVertex* pCustomVertices,
		FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f) const
	{
		m_pDX->SetRectTexUV(pCustomVertices, startTU, startTV, endTU, endTV);
	}

	inline VOID SetRectColor(CustomVertex *pCustomVertices, DWORD color) const
	{
		m_pDX->SetRectColor(pCustomVertices, color);
	}

	inline VOID CreateRect(CustomVertex *pCustomVertices, const D3DXVECTOR3& rCenter, const D3DXVECTOR3& rHalfScale,
		DWORD color = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f) const
	{
		m_pDX->CreateRect(pCustomVertices, rCenter, rHalfScale, color, startTU, startTV, endTU, endTV);
	}

	//inline VOID Render(const FbxRelated& rFBXModel, const D3DXMATRIX& pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	//{
	//	m_pRenderer->Render(rFBXModel, pMatWorld, pTexture);
	//}

	inline VOID Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX->Render(pCustomVertices, pTexture);
	}

	inline BOOL MouseIsPressed(INT key) const
	{
		return m_pDX->MouseIsPressed(key);
	}

	inline BOOL MouseIsHeld(INT key) const
	{
		return m_pDX->MouseIsHeld(key);
	}

	inline BOOL MouseIsReleased(INT key) const
	{
		return m_pDX->MouseIsReleased(key);
	}

	inline BOOL MouseIsNeutral(INT key) const
	{
		return m_pDX->MouseIsNeutral(key);
	}

	inline BOOL KeyboardIsPressed(INT key) const
	{
		return m_pDX->KeyboardIsPressed(key);
	}

	inline BOOL KeyboardIsHeld(INT key) const
	{
		return m_pDX->KeyboardIsHeld(key);
	}

	inline BOOL KeyboardIsReleased(INT key) const
	{
		return m_pDX->KeyboardIsReleased(key);
	}

	inline BOOL KeyboardIsNeutral(INT key) const
	{
		return m_pDX->KeyboardIsNeutral(key);
	}

private:
	GameLib() {};

	static Wnd* m_pWnd;

	static DX* m_pDX;
};

#endif // !GAME_LIB_H
