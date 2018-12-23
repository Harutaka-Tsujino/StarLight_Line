#ifndef PLAYER_RESULT_DATA_H_
#define PLAYER_RESULT_DATA_H_

#include <vector>

#include "../../../Obj.h"
#include "../../../../../../../.././../GameLib/GameLib.h"
#include "../../GameCollision/GameCollision.h"
#include "../../../../../../Data/ResultData.h"

class PlayerResultData :public Obj
{
public:
	PlayerResultData() :Obj(OT_UI, 0.0f), m_rGameCollision(GameCollision::GetInstance())
	{
		Init();
	}

	~PlayerResultData()
	{
		m_rGameLib.ReleaseTex();
		Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

	//セットしたときにスコアに足す
	inline VOID SetScore(const INT& Score)
	{
		m_Data.m_score += Score;
	}

	//失敗したかを受け取る
	inline VOID SetResultData(const BOOL& IsFailed)
	{
		m_Data.m_isFailed = IsFailed;
	}

	inline ResultData GetResultData() { return m_Data; }

	inline VOID JudgeGameFailure(INT necessaryNum)
	{
		m_Data.m_isFailed = !(m_Data.m_clearStarsNum >= necessaryNum);

		return;
	}

private:
	//スコアの桁が繰り上がったら
	//矩形を作り、桁数を上げる処理をする関数
	VOID IncreaseDigit(const INT& Type);

	//数字フォントのTuTv切り取り関数
	VOID DisplayNum(TexUV* UV, const INT& Num);

	//vectorの解放関数
	VOID Release();

	std::vector<CustomVertex*> m_ScoreFont;
	std::vector<INT> m_ScoreDigit;

	std::vector<CustomVertex*> m_ClearStarNumsFont;
	std::vector<INT> m_ClearStarNumsDigit;

	ResultData m_Data;

	GameCollision& m_rGameCollision;
};

#endif // !PLAYER_RESULT_DATA_H_
