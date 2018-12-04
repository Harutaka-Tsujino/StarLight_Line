#ifndef MAIN_SCENE_OBJECT_H_
#define MAIN_SCENE_OBJECT_H_

#include <Windows.h>

#include <vector>

#include "../Obj.h"
#include "../../../../../../../GameLib/GameLib.h"

class MainBack :public Obj
{
public:
	MainBack() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~MainBack() 
	{
		m_rGameLib.ReleaseTex();
	}

	VOID Init();
	VOID Update() {};
	VOID Render();
};

class PlayerLifeFrame :public Obj
{
public:
	PlayerLifeFrame():Obj(OT_UI,1.0f)
	{
		Init();
	}

	~PlayerLifeFrame()
	{
		m_rGameLib.ReleaseTex();
	}

	VOID Init();
	VOID Update() {};
	VOID Render();
};

class PlayerScoreFrame :public Obj
{
public:
	PlayerScoreFrame() :Obj(OT_UI, 1.0f)
	{
		Init();
	}

	~PlayerScoreFrame()
	{
		m_rGameLib.ReleaseTex();
	}

	VOID Init();
	VOID Update() {};
	VOID Render();
};

class PlayerScore:public Obj
{
public:
	PlayerScore() :Obj(OT_UI, 1.0f)
	{
		Init();
	}

	~PlayerScore()
	{
		m_rGameLib.ReleaseTex();
		Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

	//セットしたときにスコアに足す
	VOID SetScore(const INT& Score)
	{
		m_Score += Score;
	}

private:
	//スコアの桁が繰り上がったら
	//矩形を作り、桁数を上げる処理をする関数
	VOID SearchDigitIncreasedAndCreateNewDigit();

	//数字フォントのTuTv切り取り関数
	VOID DisplayNum(TexUV* UV,const INT& Num);

	//vectorの解放関数
	VOID Release();

	INT m_Score = 0;

	std::vector<CustomVertex*> m_ScoreFont;
	std::vector<INT> m_Digit;
};

#endif // !MAIN_SCENE_OBJECT_H_