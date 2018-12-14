#include "Camera.h"

#include <windows.h>

#include <d3dx9.h>

VOID Camera::SetTransform()
{
	D3DXMatrixLookAtLH(
		&m_view,
		&m_cameraPos,
		&m_eyePt,
		&m_cameraOverhead);

	m_rpDX3D_DEV->SetTransform(D3DTS_VIEW, &m_view);

	D3DVIEWPORT9 viewPort;
	m_rpDX3D_DEV->GetViewport(&viewPort);
	FLOAT aspect = static_cast<FLOAT>(viewPort.Width) / static_cast<FLOAT>(viewPort.Height);

	const INT DEFAULT_EYE_RADIAN = 60;

	const FLOAT DEFAULT_NEAR	= 0.01f;	//0.0fにすると全ての物体のz値が0.0fになる
	const FLOAT DEFAULT_FAR		= 10000.0f;

	D3DXMatrixPerspectiveFovLH(
		&m_proj,
		D3DXToRadian(DEFAULT_EYE_RADIAN),
		aspect,
		DEFAULT_NEAR,
		DEFAULT_FAR);

	m_rpDX3D_DEV->SetTransform(D3DTS_PROJECTION, &m_proj);
}

D3DXVECTOR3 Camera::TransScreen(const D3DXVECTOR3& Pos)
{
	D3DVIEWPORT9 ViewPort;
	m_rpDX3D_DEV->GetViewport(&ViewPort);

	D3DXVECTOR2 ScreenMat(static_cast<FLOAT>(ViewPort.Width * 0.5f),
		static_cast<FLOAT>(ViewPort.Height * 0.5f));

	D3DXMATRIX ViewPortMat =
	{
		ScreenMat.x ,	0 ,				0 , 0 ,
		0 ,				-ScreenMat.y ,	0 , 0 ,
		0 ,				0 ,				1 , 0 ,
		ScreenMat.x ,	ScreenMat.y ,	0 , 1
	};

	D3DXVECTOR3 ScreenPos, Tmp;
	D3DXVec3TransformCoord(&Tmp, &Pos, &m_view);
	D3DXVec3TransformCoord(&Tmp, &Tmp, &m_proj);

	/*Tmp.x /= Tmp.z;
	Tmp.y /= Tmp.z;
	Tmp.z /= Tmp.z;*/

	D3DXVec3TransformCoord(&ScreenPos, &Tmp, &ViewPortMat);

	return ScreenPos;
}

D3DXVECTOR3 Camera::TransWorld(const D3DXVECTOR3& Pos)
{
	D3DVIEWPORT9 ViewPort;
	m_rpDX3D_DEV->GetViewport(&ViewPort);

	D3DXVECTOR2 Screen(static_cast<FLOAT>(ViewPort.Width * 0.5f),
		static_cast<FLOAT>(ViewPort.Height * 0.5f));

	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, &m_view);
	D3DXMatrixInverse(&InvPrj, NULL, &m_proj);
	D3DXMATRIX ViewPortMat =
	{
		Screen.x, 0 ,		 0, 0,
		0,		  -Screen.y, 0, 0,
		0,		  0  ,		 1, 0,
		Screen.x, Screen.y,  0, 1
	};

	D3DXMatrixInverse(&InvViewport, NULL, &ViewPortMat);

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVECTOR3 WorldPos;

	D3DXVec3TransformCoord(&WorldPos, &Pos, &tmp);

	return WorldPos;
}
