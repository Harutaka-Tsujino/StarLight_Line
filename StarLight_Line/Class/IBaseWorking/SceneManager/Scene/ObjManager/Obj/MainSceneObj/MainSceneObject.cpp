#include "MainSceneObject.h"

#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"

VOID MainBack::Init()
{
	m_rGameLib.CreateFbx(_T("Boad"), "3DModels/Back/Boad.fbx");
	m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/Main/main_line.png"));
}

VOID MainBack::Render()
{
	//m_rGameLib.SetCameraTransform();

	//D3DXMATRIX MatWorld ,MatTrans, MatScale;
	//D3DXMatrixIdentity(&MatWorld);
	//D3DXMatrixIdentity(&MatTrans);
	//D3DXMatrixIdentity(&MatScale);

	//const float MODELSCALE = 0.05f;

	//// 拡大
	//D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);

	//// 掛け合わせ
	//D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatScale);

	//// 移動
	//D3DXMatrixTranslation(&MatTrans, 0.01f, 0.01f, 1.f);

	//// 掛け合わせ
	//D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTrans);

	//FbxRelated& rBack = m_rGameLib.GetFbx(_T("Boad"));
	//const LPDIRECT3DTEXTURE9& rTex = m_rGameLib.GetTex(_T("Back"));

	//m_rGameLib.Render(rBack, MatWorld, rTex);
}