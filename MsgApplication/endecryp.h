#pragma once
class endecryp
{
public:
	void setKeys(UINT priv1, UINT pub1, UINT mod1);
	UINT encrypt(TCHAR c);
	TCHAR decrypt(UINT cint);
};

