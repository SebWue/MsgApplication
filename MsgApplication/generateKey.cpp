#include <Windows.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>			//not used, there for writing into a file, like a .txt
#include "generateKey.h"

using namespace std;
#include "endecryp.h"
UINT q, p, n, m, e, d;
vector<UINT> primes, partofm;
int pos;
BOOL isprime = true, isnotprime = true;
UINT priv2 = 0, pub2 = 0, mod2 = 0;
void generateKey::generate(){

	srand((unsigned)time(NULL) * clock());
	// create a List of 2094 primes that get randomly chosen from
	for (int n = 3; n < 20000; n++) {
		isprime = true;
		for (int i = 2; i < n; i++) {
			if ((n % i) == 0) {
				isprime = false;
				break;
			}
		}
		if (isprime) {
			primes.push_back(n);
		}
	}
	do {
		//set p and q to randomly chosen primes from the list
		q = primes[(rand() % (100 + 1))];

		p = primes[(rand() % (100 + 1))];
		//calculate n and m
		n = p * q;

		m = (p - 1) * (q - 1);

		//getting a list of numbers that make out m in a multiplication
		UINT mcurr = m, temp;
		for (int i = 2; i < 20000; i++) {
			isnotprime = true;
			while (isnotprime) {

				if (i > mcurr) {
					break;
				}

				else {
					if (mcurr % i == 0) {
						mcurr /= i;
						partofm.push_back(i);
					}
					else {
						isnotprime = false;
					}
				}
			}
		}
		cout << endl;
		for (int i = 0; i < partofm.size(); i++) {
			cout << partofm[i] << " ";
		}
		cout << endl;
		//checking if e is smaller than m and not part of the divisor list from m
		BOOL running = true;
		while (running) {
			e = primes[(rand() % (194 + 1))];
			for (int i = 0; i < partofm.size(); i++) {
				if (e != partofm[i] && e < m) {
					running = false;
					break;
				}
			}
		}


		// Eukliclidischer Algorithmus to calculate d
		BOOL fin = false;
		int a = 0, b = 1, ind, prevb;
		vector<long> divis;
		int cdivis = 0;
		UINT tempe = e, tempm = m, modulo;

		//dividing e and m until modulo is 0
		while (true) {
			divis.push_back(tempe / tempm);
			modulo = tempe % tempm;
			if (modulo != 0) {
				tempe = tempm;
				tempm = modulo;
				if (tempe < tempm) {
					tempm = tempe;
					tempe = modulo;
				}
			}
			if (modulo == 0) {
				break;
			}
			cdivis++;
		}

		//finaly get d
		int tempi;
		//repeat the formula b = a - (e/m * b) until the first entry in divis
		for (int i = cdivis - 1; i >= 0; i--) {
			tempi = i;
			prevb = b;
			b = a - divis[i] * b;
			a = prevb;
		}

		//because d > 0, we have to add m to it
		ind = a;

		if (ind < 0) {
			d = ind + m;
		}
		else { d = ind; }
	} while (m > 6000);
	cout <<"q:   " << q << "   p:   " << p << "   n:   " << n << "   m:  "<< m << "     e:    " << e << " d: " << d << "    \n";

	wfstream keys;
	keys.open("keys.txt");
	keys.clear();
	keys << L"N" << n << ";E" << e << ";D" << d << ";";
	keys.close();

	pub2 = e;
	priv2 = d;
	mod2 = n;
}


BOOL keyExis = false;

BOOL checkKey() {
	BOOL keyThere = false;
	wfstream keys;
	keys.open("keys.txt");
	string cs; //= getline();
	if (cs.size() == NULL){
		keyThere = false;
	}
	keys << "                                                                  ";
	keys.close();

	//if(keys.read())

	return keyThere;
}

void generateKey::newThreadToCheck()
{
	endecryp set;

	keyExis = checkKey();
	if (!keyExis) {
		generate();
	}

	set.setKeys(priv2, pub2, mod2);
}
