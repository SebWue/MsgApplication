#include <iostream>		//needed for a lot
#include <vector>		//needed for clac.h
#include <Windows.h>	//needed for Windows spezific variables
#include <math.h>
#include <chrono>
#include <thread>
using namespace std::chrono;
using namespace std;
#include "countS.h"
#include "calcW.h"
#include "endecryp.h"


UINT priv, pub, mod;

void endecryp::setKeys(UINT priv1, UINT pub1, UINT mod1)
{
	priv = priv1;
	pub = pub1;
	mod = mod1;
}

void endecryp::getKeys(UINT &priv1, UINT &pub1, UINT &mod1)
{
	priv1 = priv;
	pub1 = pub;
	mod1 = mod;
}
UINT endecryp::encrypt(TCHAR c)
{
	//starting a counter
	countS countS;
	calcW calcW;

	auto start = high_resolution_clock::now();

	UINT cint = (UINT)c;
	vector<int> cintarr;
	cintarr = calcW.turninttoarray(cint);
	cintarr = calcW.lpow(cintarr, pub);
	cint = calcW.lmod(cintarr, mod);

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<seconds>(stop - start);
	cout << duration.count() << " ";

	return cint;
}

TCHAR endecryp::decrypt(UINT cint)
{

	auto start = high_resolution_clock::now();

	calcW calcW;
	TCHAR c;
	vector<int>cintarr;
	cintarr = calcW.turninttoarray(cint);
	cintarr = calcW.lpow(cintarr, priv);
	cint = calcW.lmod(cintarr, mod);
	c = (TCHAR)cint;

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<seconds>(stop - start);
	cout << duration.count() << " ";

	return c;
}
