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

struct TextFormat
{
public:
	D3DXVECTOR2 m_topLeft = { 0.0f, 0.0f };
	RectSize m_charHalfScale = { 0, 0 };
	D3DXVECTOR2 m_charGap = { 0.0f,0.0f };
	DWORD m_color = 0xEEF8F8F8;
};

#endif //! TEXT_FORMAT_H
