#ifndef PLAYER_ONE_H_
#define PLAYER_ONE_H_

#include "../../../MainSceneObj/Player/PlayerBase/PlayerBase.h"

class PlayerOne :public PlayerBase
{
public:
	PlayerOne()
	{
		Init();
	}

	~PlayerOne()
	{
		m_rGameLib.GetFbx(_T("Eiwi")).Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	VOID SetPlayerFbxMaterial();

	Joycon::CONTROLLER_TYPE m_contrllerType = Joycon::LEFT_CONTROLLER;
};

#endif // !PLAYER_ONE_H_
