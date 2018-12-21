/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef T_STRING_H
#define T_STRING_H

#include <windows.h>
#include <tchar.h>

#include <vector>

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

	inline VOID Shift(INT movement)
	{
		m_textPtr += movement;
	}

	inline VOID Locate(INT pos)
	{
		m_textPtr = pos;
	}

	inline VOID WriteInAll(const TCHAR* pText)
	{
		Reset();

		for (INT i = 0; IsTextEnd(pText[i]); ++i) m_tChar.push_back(pText[i]);

		m_tChar.push_back(m_TEXT_END);
	}

	inline VOID WriteOutAll(TString* pTString) const
	{
		pTString->Reset();

		TCHAR buf = NULL;

		for (INT i = 0; (buf = m_tChar[i]) != m_TEXT_END; ++i)
		{
			pTString->WriteInChar(buf);
		}

		pTString->WriteInChar(m_TEXT_END);
	}

	inline VOID WriteOutAll(TCHAR* pText)
	{
		for (INT i = 0; i < Size(); ++i) pText[i] = m_tChar[i];
	}

	inline TCHAR GetTChar()
	{
		if (TextPtrPointsToEndOfText()) return;

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
		if (TextPtrPointsToEndOfText()) return;

		for (; isLineOrTextEnd(m_tChar[m_textPtr]); ++m_textPtr) pTString->WriteInChar(m_tChar[m_textPtr]);

		pTString->WriteInChar(m_TEXT_END);

		m_textPtr += m_NEW_LINE_AND_RETURN_LENGTH;	//! \nと\rを飛ばす
	}

	inline BOOL TextPtrPointsToEndOfText() const
	{
		return (m_textPtr >= Size() - 1);
	}

	inline BOOL LastCharIsTextEnd()
	{
		INT lastElement = m_tChar.size() - 1;
		return IsTextEnd(m_tChar[lastElement]);
	}

	inline INT Size() const
	{
		return m_tChar.size();
	}

	inline INT Length() const
	{
		INT length = 0;

		for (INT i = 0; IsLineEnd(m_tChar[i]); ++i) ++length;

		return length;
	}

	static const INT m_NEW_LINE_AND_RETURN_LENGTH = 2;

	static const TCHAR m_NEW_LINE = _T('\n');
	static const TCHAR m_TEXT_END = _T('\0');

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
	INT m_textPtr = 0;
};

#endif //! T_STRING_H
