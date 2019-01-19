#ifndef PLAYER_H_
#define PLAYER_H_

#include <Windows.h>

#include <d3dx9.h>

#include "PlayerBase/PlayerBase.h"

/**
*@brief 自機クラス
*/
class Player :public PlayerBase
{
public:
	Player()
	{
		Init();
	}

	~Player()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();

		m_ResultData.JudgeGameFailure(8); //引数は適当

		if (m_Hp.GetHP() <= 0 && !rSceneManager.GetIsTutorial())
		{
			m_ResultData.SetResultData(TRUE);
		}

		rSceneManager.SetResultData(m_ResultData.GetResultData());

		m_rGameLib.GetFbx(_T("Eiwi")).Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	/**
	*@brief 生存している場合に、スコアを獲得する関数
	*@param LevelScore 難易度によってスコアを獲得できる
	*/
	VOID ObtainScoreToExist(const INT& LevelScore);

	VOID DecideColorByHit(FLOAT* pAdditionalColor);

	VOID SetPlayerFbxMaterial();

	INT count;		//生存スコアを手に入れるところで使う

	StageData m_StageData;
	PlayerResultData m_ResultData;
	PlayerHP m_Hp;
};

#endif // !PLAYER_H_
