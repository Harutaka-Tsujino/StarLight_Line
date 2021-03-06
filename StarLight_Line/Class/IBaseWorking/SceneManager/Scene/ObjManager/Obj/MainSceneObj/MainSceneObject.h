﻿#ifndef MAIN_SCENE_OBJECT_H_
#define MAIN_SCENE_OBJECT_H_

#include <Windows.h>

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

class MainLine :public Obj
{
public:
	MainLine() :Obj(OT_UI, 1.0f)
	{
		Init();
	}

	~MainLine()
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

class PlayerClearStarObj :public Obj
{
public:
	PlayerClearStarObj() :Obj(OT_UI, 1.0f)
	{
		Init();
	}

	~PlayerClearStarObj()
	{
		m_rGameLib.ReleaseTex();
	}

	VOID Init();
	VOID Update() {};
	VOID Render();

private:
	VOID RenderFrame();
	VOID RenderStarObtained();
};

#endif // !MAIN_SCENE_OBJECT_H_
