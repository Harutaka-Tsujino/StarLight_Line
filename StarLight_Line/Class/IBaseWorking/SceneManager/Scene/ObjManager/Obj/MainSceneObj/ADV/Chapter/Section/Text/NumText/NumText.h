#ifndef NUM_TEXT_H
#define NUM_TEXT_H

#include <windows.h>
#include <tchar.h>

#include "../Text.h"

class NumText :public Text
{
public:
	NumText(const TString& text, const TCHAR* pFontTexPath) :Text(text, pFontTexPath) {};
	~NumText() {};

private:
	VOID CreateOneLineCharsRects(const TextFormat& textFormat, std::vector<ObjData*>* ppCharDatas,
		std::vector<CustomVertex*>* ppChars, std::vector<TString*>& pOneLineStrings) const;
};

#endif // !NUM_TEXT_H
