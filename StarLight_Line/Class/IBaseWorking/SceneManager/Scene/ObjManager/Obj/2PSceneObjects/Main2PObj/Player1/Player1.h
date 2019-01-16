#ifndef PLAYER_ONE_H_
#define PLAYER_ONE_H_

#include <tchar.h>

#include "../../../MainSceneObj/Player/PlayerBase/PlayerBase.h"
#include "../../../MainSceneObj/Player/PlayerResultData/2PResultData/2PResultData.h"

class PlayerOne :public PlayerBase
{
public:
	PlayerOne()
	{
		Init();
	}

	~PlayerOne()
	{
		delete m_pOnePlayerData;
		m_rGameLib.GetFbx(_T("Eiwi")).Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	VOID SetPlayerFbxMaterial();

	TwoPlayerResultData* m_pOnePlayerData;
	Joycon::CONTROLLER_TYPE m_contrllerType = Joycon::LEFT_CONTROLLER;
};

#endif // !PLAYER_ONE_H_
