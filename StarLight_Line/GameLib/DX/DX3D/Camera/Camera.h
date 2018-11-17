#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>

#include <d3dx9.h>

class Camera
{
public:
	Camera(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};
	~Camera() {};

	inline VOID GetCameraPos(D3DXVECTOR3* pCameraPos) const
	{
		pCameraPos->x = m_cameraPos.x;
		pCameraPos->y = m_cameraPos.y;
		pCameraPos->z = m_cameraPos.z;
	}

	inline VOID SetCameraPos(FLOAT x, FLOAT y, FLOAT z)
	{
		m_cameraPos.x = x;
		m_cameraPos.y = y;
		m_cameraPos.z = z;
	}

	inline VOID SetCameraPos(const D3DXVECTOR3& rCameraPos)
	{
		m_cameraPos.x = rCameraPos.x;
		m_cameraPos.y = rCameraPos.y;
		m_cameraPos.z = rCameraPos.z;
	}

	inline VOID GetEyePt(D3DXVECTOR3* pEyePoint) const
	{
		pEyePoint->x = m_eyePt.x;
		pEyePoint->y = m_eyePt.y;
		pEyePoint->z = m_eyePt.z;
	}

	inline VOID SetEyePt(FLOAT x, FLOAT y, FLOAT z)
	{
		m_eyePt.x = x;
		m_eyePt.y = y;
		m_eyePt.z = z;
	}

	inline VOID SetEyePt(const D3DXVECTOR3& rEyePt)
	{
		m_eyePt.x = rEyePt.x;
		m_eyePt.y = rEyePt.y;
		m_eyePt.z = rEyePt.z;
	}

	inline VOID GetView(D3DXMATRIX* pView) const
	{
		*pView = m_view;
	}

	inline VOID GetProj(D3DXMATRIX* pProj) const
	{
		*pProj = m_proj;
	}

	VOID SetTransform();

	inline VOID TransBillBoard(D3DXMATRIX* pWorld) const
	{
		D3DXMATRIX viewInverse;
		D3DXMatrixInverse(
			&viewInverse,
			NULL,
			&m_view);

		D3DXMatrixMultiply(
			pWorld,
			pWorld,
			&viewInverse);
	}

private:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;

	D3DXVECTOR3 m_cameraPos			= { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_eyePt				= { 0.0f,0.0f,1.0f };
	D3DXVECTOR3 m_cameraOverhead	= { 0.0f,1.0f,0.0f };

	D3DXMATRIX m_view;
	D3DXMATRIX m_proj;
};

#endif // !CAMERA_H
