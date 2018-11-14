#ifndef I_DX_INPUT_H
#define I_DX_INPUT_H

#include <dinput.h>

class IDXInput
{
public:
	virtual const LPDIRECTINPUT8& GetLPDIRECTINPUT8() = 0;
};

#endif // !I_DX_INPUT_H
