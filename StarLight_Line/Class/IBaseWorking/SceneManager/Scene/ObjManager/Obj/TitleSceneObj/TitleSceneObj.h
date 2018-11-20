#ifndef TITLE_SCENE_OBJ_H
#define TITLE_SCENE_OBJ_H

#include <windows.h>

#include "../Obj.h"
#include "../../../TitleScene/TitleScene.h"
#include "../../../../../../../GameLib/GameLib.h"

//class TitleBack :public Obj
//{
//public:
//	TitleBack(TitleScene& rTitleScene) :Obj(OT_BACK, 1.0f), m_rTitleScene(rTitleScene)
//	{
//		Init();
//	}
//
//	~TitleBack()
//	{
//
//	};
//
//	inline VOID Init() const
//	{
//		static BOOL isInitialized = FALSE;
//		if (isInitialized)
//		{
//			return;
//		}
//
//		m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/Title/title_background.png"));
//	}
//
//	inline VOID Update() const {};
//
//	inline VOID Render() const
//	{
//		ObjData back;
//		back.m_center = { m_windowSize.x*0.5f,m_windowSize.y*0.5f,1.0f };
//		back.m_halfScale = { m_windowSize.x * 0.5f ,m_windowSize.y * 0.5f,0.0f };
//
//		CustomVertex back[4];
//		m_rGameLib.CreateRect(back, &data);								//頂点データの作成
//
//		m_pGameManager->Render(back, m_pGameManager->GetTex(_T("Back")));		//描画
//	}
//
//public:
//	TitleScene& m_rTitleScene;
//};
//
//class TitleLogo :public Obj
//{
//public:
//	TitleLogo(Scene* pScene);
//	~TitleLogo() {};
//
//	VOID Init();
//	VOID Update() {};
//	VOID Render();
//};
//
//class TitleInputPrompt :public Obj
//{
//public:
//	TitleInputPrompt(Scene* pScene);
//	~TitleInputPrompt() {};
//
//	VOID Init();
//	VOID Update();
//	VOID Render();
//
//public:
//	VOID SetAlpha();
//	VOID ChangeFlashStrength();
//
//	ObjData m_data;
//	const INT M_FLASH_COUNT_MAX = 127;		//flashCountの最大値
//	UCHAR m_flashCount = M_FLASH_COUNT_MAX;	//テキストの点滅に用いるカウンタ
//};
//
//class TitleMenu :public Obj
//{
//public:
//	TitleMenu(Scene* pScene);
//	~TitleMenu() {};
//
//	VOID Init();
//	VOID Update();
//	VOID Render();
//
//private:
//	enum MenuID
//	{
//		NEW_GAME,
//		LOAD_GAME,
//		END_GAME,
//		MENU_MAX
//	};
//
//	VOID RotateMenuUp();
//	VOID RotateMenuDown();
//	BOOL PreventDecideMenuUnintended();								//意図しないメニュー選択を防ぐ関数 trueならreturnする
//	VOID SelectMenu();												//メニューを選択する関数
//
//	MenuID m_menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };	//表示用メニューの並び
//	const INT M_SELECTING_MENU = 1;									//現在選ばれているメニューが入っているmenuReelの要素番号
//};
//
//class TitleStarEffect :public Obj
//{
//public:
//	TitleStarEffect(Scene* pScene);
//	~TitleStarEffect() {};
//
//	VOID Init();
//	VOID Update() {};
//	VOID Render();
//
//private:
//	struct starEffect
//	{
//	public:
//		BOOL m_canInit = true;
//		D3DXVECTOR3 m_movement;
//		ObjData m_data;
//		CustomVertex m_vertices[4];
//	};
//
//	VOID InitStarEffects(starEffect* pStarEffect);
//
//	D3DXVECTOR3 m_halfstarEffectScale;		//0.0027,0.6　デフォルトの大きさ
//	D3DXVECTOR3 m_unitStarEffectMovement;	//速度
//
//};
//
//class TitleSmallStarEffect :public Obj
//{
//public:
//	TitleSmallStarEffect(Scene* pScene);
//	~TitleSmallStarEffect() {};
//
//	VOID Init();
//	VOID Update() {};
//	VOID Render();
//private:
//	struct SmallStarEffect
//	{
//	public:
//		BOOL m_canCountUp = true;
//		INT m_flashCount = TitleSmallStarEffect::M_INIT_COUNT;
//		ObjData m_data;
//		D3DXVECTOR4 m_aRGB;
//		CustomVertex m_vertices[4];
//	};
//
//	static const INT M_INIT_COUNT = -1;
//	const INT M_FLASH_COUNT_MAX = 210;
//	const INT M_FLASH_COUNT_MIN = 20;
//};

#endif // !TITLE_SCENE_OBJ_H
