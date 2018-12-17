/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef TEXT_H
#define TEXT_H

#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "../../../../../../../../../../../GameLib/GameLib.h"
#include "Data\TextFormat.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../../../../../../../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

class Text
{
public:
	Text(const TCHAR* pText, const TCHAR* pFontTexPath) :m_rGameLib(GameLib::GetInstance())
	{
		m_text.WriteInAll(pText);

		DivideTextByNewLine();

		if (m_rGameLib.TexExists(m_pFONT_KEY)) return;

		m_rGameLib.CreateTex(m_pFONT_KEY, pFontTexPath);
	}

	~Text()
	{
		std::for_each(m_pOneLineTstringVec.begin(), m_pOneLineTstringVec.end(), [](TString* pI) { delete pI; });
	}

	VOID Write(const TextFormat& textFormat)
	{
		std::vector<ObjData*> pCharData;
		std::vector<CustomVertex*> pCustomVerticesVec;

		NewCustomVerticesData(&pCharData, &pCustomVerticesVec);

		size_t oneLineLength = NULL;

		FLOAT halfX = static_cast<FLOAT>(textFormat.m_charHalfScale.m_x);
		FLOAT halfY = static_cast<FLOAT>(textFormat.m_charHalfScale.m_y);

		const size_t RECT_VERTICES_NUM = CustomVertex::m_RECT_VERTICES_NUM;

		for (INT si = 0; si < m_pOneLineTstringVec.size(); ++si)
		{
			oneLineLength = m_pOneLineTstringVec[si]->Length();

			for (INT li = 0; li < oneLineLength; ++li)
			{
				pCharData[si][li].m_center =
				{
					textFormat.m_topLeft.x + halfX + li * (2 * halfX + textFormat.m_charGap.x),
					textFormat.m_topLeft.y + halfY + si * (2 * halfY + textFormat.m_charGap.y),
					1.0f
				};

				textFormat.m_charHalfScale.TransD3DXVECTOR3(&pCharData[si][li].m_halfScale);

				m_rGameLib.CreateRect(&pCustomVerticesVec[si][RECT_VERTICES_NUM * li], pCharData[si][li]);

				m_rGameLib.Render(&pCustomVerticesVec[si][RECT_VERTICES_NUM * li], m_rGameLib.GetTex(m_pFONT_KEY));
			}
		}

		ReleaseCustomVerticesData(&pCharData, &pCustomVerticesVec);
	}

protected:
	class TString
	{
	public:
		TString() {};

		explicit TString(const TCHAR* pText)
		{
			WriteInAll(pText);
		}

		~TString() {};

		inline VOID Reset()
		{
			m_textPtr = 0;

			m_tChar.clear();
			m_tChar.shrink_to_fit();
		}

		inline VOID SeekFirst()
		{
			m_textPtr = 0;
		}

		inline VOID Shift(size_t movement)
		{
			m_textPtr += movement;
		}

		inline VOID Locate(size_t pos)
		{
			m_textPtr = pos;
		}

		inline VOID WriteInAll(const TCHAR* pText)
		{
			Reset();

			for (size_t i = 0; IsTextEnd(pText[i]); ++i) m_tChar.push_back(pText[i]);

			m_tChar.push_back(m_TEXT_END);
		}

		inline VOID WriteOutAll(TCHAR* pText)
		{
			for (size_t i = 0; i < Size(); ++i) pText[i] = m_tChar[i];
		}

		inline TCHAR GetTChar()
		{
			if (TextPtrPointToEndOfText()) return;

			TCHAR buf = m_tChar[m_textPtr];
			++m_textPtr;

			return buf;
		}
		
		inline VOID WriteInChar(TCHAR tChar)
		{
			m_tChar.push_back(tChar);
		}

		inline VOID GetLine(TString* pTString)
		{
			if (TextPtrPointToEndOfText()) return;

			for (; isLineOrTextEnd(m_tChar[m_textPtr]); ++m_textPtr) pTString->WriteInChar(m_tChar[m_textPtr]);

			pTString->WriteInChar(m_TEXT_END);

			++m_textPtr;
		}

		inline BOOL TextPtrPointToEndOfText() const
		{
			return (m_textPtr >= Size() - 1);
		}

		inline size_t Size() const
		{
			return m_tChar.size();
		}

		inline size_t Length() const
		{
			size_t length = 0;

			for (INT i = 0; IsLineEnd(m_tChar[i]); ++i) ++length;

			return length;
		}

		const TCHAR m_NEW_LINE = _T('\n');
		const TCHAR m_TEXT_END = _T('\0');

	private:
		inline BOOL IsLineEnd(const TCHAR tChar) const
		{
			return (tChar == m_NEW_LINE);
		}

		inline BOOL IsTextEnd(const TCHAR tChar) const
		{
			return (tChar == m_TEXT_END);
		}

		inline BOOL isLineOrTextEnd(const TCHAR tChar) const
		{
			return (IsLineEnd(tChar) || IsTextEnd(tChar));
		}

		std::vector<TCHAR> m_tChar;
		size_t m_textPtr = 0;
	};

	inline VOID DivideTextByNewLine()
	{
		TString* pTString = nullptr;

		while (m_text.TextPtrPointToEndOfText())
		{
			pTString = new TString();

			m_text.GetLine(pTString);

			m_pOneLineTstringVec.push_back(pTString);
		}
	}

	inline VOID NewCustomVerticesData(std::vector<ObjData*>* ppCharData, std::vector<CustomVertex*>* ppCustomVerticesVec) const
	{
		size_t oneLineTextNum = m_pOneLineTstringVec.size();
		size_t oneLineLength = NULL;
		for (INT i = 0; i < oneLineTextNum; ++i)
		{
			oneLineLength = m_pOneLineTstringVec[i]->Length();

			ppCharData->push_back(new ObjData[oneLineLength]);
			ppCustomVerticesVec->push_back(new CustomVertex[CustomVertex::m_RECT_VERTICES_NUM * oneLineLength]);
		}
	}

	inline VOID ReleaseCustomVerticesData(std::vector<ObjData*>* ppCharData, std::vector<CustomVertex*>* ppCustomVerticesVec) const
	{
		size_t oneLineTextNum = m_pOneLineTstringVec.size();
		size_t oneLineLength = NULL;
		for (INT i = 0; i < oneLineTextNum; ++i)
		{
			oneLineLength = m_pOneLineTstringVec[i]->Length();

			delete[] (*ppCharData)[i];
			delete[] (*ppCustomVerticesVec)[i];
		}
	}

	GameLib& m_rGameLib;

	const TCHAR* m_pFONT_KEY = _T("Font");

	TString m_text;
	std::vector<TString*> m_pOneLineTstringVec;
};

#endif //! TEXT_H
