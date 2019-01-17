#ifndef TWO_PLAYER_RESULT_DATA_H_
#define TWO_PLAYER_RESULT_DATA_H_

#include <vector>

#include "../../../../../../../SceneManager.h"
#include "../../../../Obj.h"
#include "../../../../../../../../.././../GameLib/GameLib.h"
#include "../../../GameCollision/GameCollision.h"
#include "../../../../../../../Data/ResultData.h"

class TwoPlayerResultData :public Obj
{
public:
	TwoPlayerResultData(const TCHAR* PlayerKey, Joycon::CONTROLLER_TYPE controllerType)
		:Obj(OT_TRANSPARENCY, 1.0f),
		m_rGameCollision(GameCollision::GetInstance()),
		m_PlayerTypeKey(PlayerKey),
		m_controllerType(controllerType)
	{
		Init();
	}

	~TwoPlayerResultData()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.Set2PModeScore(m_controllerType, m_Score);

		m_rGameLib.ReleaseTex();
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	INT m_Score;
	const TCHAR* m_PlayerTypeKey;	//当たり判定用
	
	Joycon::CONTROLLER_TYPE m_controllerType;
	GameCollision& m_rGameCollision;
};

#endif // !TWO_PLAYER_RESULT_DATA_H_
