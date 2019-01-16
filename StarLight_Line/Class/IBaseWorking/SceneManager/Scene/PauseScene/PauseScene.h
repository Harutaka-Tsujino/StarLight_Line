#ifndef PAUSE_SCENE_H_
#define PAUSE_SCENE_H_

#include "../../SceneManager.h"
#include "../Scene.h"
#include "../../../../../GameLib/GameLib.h"
#include "../../../../../GameLib/Wnd/Wnd.h"

class PauseScene :public Scene
{
public:
	PauseScene() :m_rGameLib(GameLib::GetInstance()), m_WND_SIZE(m_rGameLib.GetWndSize())
	{
		Init();
	}

	~PauseScene() 
	{
		m_rGameLib.EraseTex(_T("PauseBack"));
		m_rGameLib.EraseTex(_T("PauseFrame"));
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	enum TRANSFER_KEY
	{
		RESUME_KEY,
		TITLE_KEY,
		STAGE_SELECT_KEY,
		RESTART_KEY,
	};

	INT m_ActivatingKey;

	VOID TransferScene(const TRANSFER_KEY& Key);

	VOID RenderPauseBack();
	VOID RenderPauseFrame();
	VOID RenderPauseEffect();

	VOID RenderPauseHead();
	VOID RenderPauseText();

	GameLib& m_rGameLib;
	const RectSize m_WND_SIZE = { 0,0 };
};

#endif // !PAUSE_SCENE_H_
