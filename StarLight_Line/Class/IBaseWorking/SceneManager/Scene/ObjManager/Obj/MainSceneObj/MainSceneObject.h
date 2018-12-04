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
	VOID SetScore(const INT& Num)
	{
		m_Score += Num;
	}

private:
	VOID SearchDigitIncreasedAndCreateNewDigit();
	VOID DisplayNum(TexUV* UV,const INT& Num);
	VOID Release();

	INT m_Score = 0;

	std::vector<CustomVertex*> m_ScoreFont;
	std::vector<INT> m_Digit;
};

#endif // !MAIN_SCENE_OBJECT_H_