#ifndef I_D3DPP_H
#define I_D3DPP_H

#include <d3dx9.h>

class ID3DPP
{
public:
	virtual inline D3DPRESENT_PARAMETERS GetD3DPRESENT_PARAMETERS() = 0;
	virtual D3DPRESENT_PARAMETERS ToggleD3DPPWndMode() = 0;
};

#endif // !I_D3DPP_H
