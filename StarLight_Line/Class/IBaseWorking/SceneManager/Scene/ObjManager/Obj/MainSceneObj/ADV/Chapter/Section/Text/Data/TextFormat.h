/// <filename>
/// TextFormat.h
/// </filename>
/// <summary>
/// Textクラスなどに用いる書式を指定する構造体のヘッダ
/// </summary>
/// <author>
/// Harutaka-Tsujino
/// </author>

#ifndef TEXT_FORMAT_H
#define TEXT_FORMAT_H

#include <d3dx9.h>

#include "../../../../../../../../../../../../GameLib/Wnd/Data/RectSize.h"

enum GRADATION_TYPE
{
	GT_NONE,
	GT_SIDE,
	GT_HIGH_LOW,
	GT_OBLIQUE_BOTTOM_RIGHT,
	GT_OBLIQUE_BOTTOM_LEFT,
	GT_MAX
};

struct TextFormat
{
public:
	D3DXVECTOR2 m_topLeft = { 0.0f, 0.0f };
	RectSize m_charHalfScale = { 0, 0 };
	D3DXVECTOR2 m_charGap = { 0.0f,0.0f };
	DWORD m_color1 = 0xEEF8F8F8;
	DWORD m_color2 = 0xEEF8F8F8;
	GRADATION_TYPE m_gradationType = GT_NONE;
};

#endif //! TEXT_FORMAT_H
