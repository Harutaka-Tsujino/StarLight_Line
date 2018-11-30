#include "MainSceneObject.h"

#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"

VOID MainBack::Init()
{
	m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/YellowAlpha58.png"));
}

VOID MainBack::Render()
{
	m_rGameLib.SetCameraTransform();

	

	for (INT i = 0; i < 4; ++i)
	{
		billBoard[i].m_aRGB = 0xFFFFCC11;
	}
	
	billBoard[0].m_x = -5.0f;
	billBoard[0].m_y = 5.0f;
	billBoard[0].m_z = 0.0f;
	billBoard[0].m_tu = 0.0f;
	billBoard[0].m_tv = 0.0f;
	
	billBoard[1].m_x = 5.0f;
	billBoard[1].m_y = 5.0f;
	billBoard[1].m_z = 0.0f;
	billBoard[1].m_tu = 1.0f;
	billBoard[1].m_tv = 0.0f;
	
	billBoard[2].m_x = 5.0f;
	billBoard[2].m_y = -5.0f;
	billBoard[2].m_z = 0.0f;
	billBoard[2].m_tu = 1.0f;
	billBoard[2].m_tv = 1.0f;
	
	billBoard[3].m_x = -5.0f;
	billBoard[3].m_y = -5.0f;
	billBoard[3].m_z = 0.0f;
	billBoard[3].m_tu = 0.0f;
	billBoard[3].m_tv = 1.0f;
	
	D3DXMATRIX matWorld, matTrans, matRotX, matRotY, matRotZ, matScale;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);
	
	// 拡大
	D3DXMatrixScaling(&matScale, 0.007f, 0.007f, 0.007f);
	
	D3DXMatrixMultiply(&matWorld, &matWorld, &matScale);
	
	// 回転
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(0.0f));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(0.0f));
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.0f));
	
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotY);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotX);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotZ);
	
	// 移動
	D3DXMatrixTranslation(&matTrans, 0.049f, -0.0285f, 0.137f);
	
	// 掛け合わせ
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTrans);
	
	//ビューの逆行列をかけてビルボード化
	rCamera.NegateView(&matWorld);
	
	rpDirectX3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	vertexBuffer->Unlock();
	
	rpDirectX3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex3D));
	
	switch (shotRenderCount)
	{
	case 1:
	
		rpDirectX3DDevice->SetTexture(0, textures[_T("mazulFlash0")]);
		break;
	case 2:
	
		rpDirectX3DDevice->SetTexture(0, textures[_T("mazulFlash1")]);
		break;
	case 3:
	
		rpDirectX3DDevice->SetTexture(0, textures[_T("mazulFlash2")]);
		break;
	case 4:
	
		rpDirectX3DDevice->SetTexture(0, textures[_T("mazulFlash3")]);
		break;
	case 5:
	
		rpDirectX3DDevice->SetTexture(0, textures[_T("mazulFlash1")]);
		break;
	}
	
	rpDirectX3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
	
	vertexBuffer->Release();
	vertexBuffer = NULL;
	}
}