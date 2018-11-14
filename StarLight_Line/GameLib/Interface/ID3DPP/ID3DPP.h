#ifndef I_D3DPP_H
#define I_D3DPP_H

class ID3DPP
{
public:
	virtual D3DPRESENT_PARAMETERS* GetD3DPRESENT_PARAMETERS() = 0;
	virtual VOID SwitchD3DPPWndMode() = 0;
};

#endif // !I_D3DPP_H
