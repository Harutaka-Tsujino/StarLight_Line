#include "Main2PScene.h"

MainTwoPlayerScene::MainTwoPlayerScene()
{
	GameLib& rGameLib = GameLib::GetInstance();

	rGameLib.SetCameraPos(0.0f, -2.15f, -1.0f);
	rGameLib.SetCameraTransform();

	m_pObjManager->Resister(static_cast<Obj*>(new PlayerTwo()));
	m_pObjManager->Resister(static_cast<Obj*>(new MainBack()));
	m_pObjManager->Resister(static_cast<Obj*>(new MainLine()));
	m_pObjManager->Resister(static_cast<Obj*>(new ScoreFrameforTwoPlayer()));
	m_pObjManager->Resister(static_cast<Obj*>(new StarManager()));
	m_pObjManager->Resister(static_cast<Obj*>(new PlayerOne()));
}
