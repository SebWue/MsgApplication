#include <Windows.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
using namespace std;
#include "calcW.h"
#include "countS.h"


vector<int> calcW::turninttoarray(int a)
{
	int temp;
	vector<int> arrnum;
	while (a != 0) {
		arrnum.push_back(temp = a % 10);
		a /= 10;
	}
	cout << endl;
	
	return arrnum;
}

vector<int> calcW::lpow(vector<int> orignum, int power) {
	vector<int> newnumber, oldnewnum;
	int tempres, tempover;

	//creating the array, in which the result is saved in
	for (int i = 0; i < orignum.size(); i++) {
		newnumber.push_back(NULL);
	}
	//saving the time the Programm started

	for (int ex = 2; ex <= power; ex++) {
		if (ex == 2) {
			for (int i = 0; i < orignum.size(); i++) {
				for (int j = 0; j < orignum.size(); j++) {
					tempres = 0, tempover = 0;
					//making sure there is enough space in the vector, so we dont get a out of bounds expression
					if ((j + i) > newnumber.size() - 1) {
						newnumber.push_back(NULL);
					}

					//actually calculating
					tempres = orignum[i] * orignum[j];
					newnumber[j + i] += tempres;

					//correcting the current number if needed
					if (newnumber[i + j] > 9) {
						tempres = newnumber[i + j];
						tempres = tempres % 10;
						tempover = newnumber[i + j];
						tempover = tempover / 10;
						if ((j + i + 1) > newnumber.size() - 1) {
							newnumber.push_back(NULL);
						}
						newnumber[i + j] = tempres;
						newnumber[i + j + 1] += tempover;
					}
				}
			}
		}
		else {
			oldnewnum = newnumber;
			for (int i = 0; i < newnumber.size(); i++) {
				newnumber[i] = 0;
			}
			for (int i = 0; i < orignum.size(); i++) {
				for (int j = 0; j < oldnewnum.size(); j++) {

					//making sure there is enough space
					if ((j + i) > newnumber.size() - 1) {
						newnumber.push_back(NULL);
					}

					//calculating
					tempres = orignum[i] * oldnewnum[j];
					newnumber[i + j] += tempres;

					if (newnumber[i + j] > 9) {
						tempres = newnumber[i + j];
						tempres = tempres % 10;
						tempover = newnumber[i + j];
						tempover = tempover / 10;
						if ((j + i + 1) > newnumber.size() - 1) {
							newnumber.push_back(NULL);
						}
						newnumber[i + j] = tempres;
						newnumber[i + j + 1] += tempover;
					}
				}
			}
		}
	}

	return newnumber;
}

int calcW::lmod(vector<int> orgnum, int divident)
{
	UINT inp = 0;
	for (int i = 0; i < orgnum.size(); i++) {
		inp += orgnum[i] * pow(10, i);
	}

	int temp = 0;

	//calculating
	for (int i = orgnum.size() - 1; i >= 0; i--) {

		temp = (temp * 10 + orgnum[i]) % divident;
	}

	return temp;
}
