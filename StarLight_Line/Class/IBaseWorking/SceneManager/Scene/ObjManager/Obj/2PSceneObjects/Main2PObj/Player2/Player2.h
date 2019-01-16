#ifndef PLAYER_TWO_H_
#define PLAYER_TWO_H_

#include <tchar.h>

#include "../../../MainSceneObj/Player/PlayerBase/PlayerBase.h"
#include "../../../MainSceneObj/Player/PlayerResultData/2PResultData/2PResultData.h"

class PlayerTwo :public PlayerBase
{
public:
	PlayerTwo()
	{
		Init();
	}

	~PlayerTwo()
	{
		delete m_pTwoPlayerData;
		m_rGameLib.GetFbx(_T("Eiwi")).Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	VOID SetPlayerFbxMaterial();

	TwoPlayerResultData* m_pTwoPlayerData;
	Joycon::CONTROLLER_TYPE m_contrllerType = Joycon::RIGHT_CONTROLLER;
};

#endif // !PLAYER_ONE_H_
