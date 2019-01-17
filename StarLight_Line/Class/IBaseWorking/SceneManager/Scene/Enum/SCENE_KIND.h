/**
* @file SCENE_KIND.h
* @brief シーンの種類列挙体のヘッダ
* @author Harutaka-Tsujino
*/

#ifndef SCENE_KIND_H
#define SCENE_KIND_H

/**
* @brief シーンの種類
*/
enum SCENE_KIND
{
	SK_TITLE,
	SK_TUTORIAL,
	SK_STAGE_SELECT,
	SK_2P_STAGE_SELECT,
	SK_GAME,
	SK_2P_GAME,
	SK_PAUSE,
	SK_SAVE_DATA,
	SK_RESULT,
	SK_2P_RESULT,
	SK_END,
	SK_MAX
};

#endif // !SCENE_ENUM_H
