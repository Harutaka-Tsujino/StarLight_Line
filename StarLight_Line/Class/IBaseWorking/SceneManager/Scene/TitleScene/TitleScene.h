#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <windows.h>

#include "../Scene.h"

class TitleScene :public Scene
{
public:
	TitleScene() {};
	~TitleScene() {};

	inline VOID Update() {};

	inline VOID Render() {};

	inline BOOL CanShowMenus() const
	{
		return m_canShowMenus;
	}

	inline VOID SetCanShowMenus(BOOL canShowMenu)
	{
		m_canShowMenus = canShowMenu;
	}

private:
	BOOL m_canShowMenus = FALSE;
};

#endif // !TITLE_SCENE_H
