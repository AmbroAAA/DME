/*
 * System.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: Ravish
 */

#include "System.h"
#include <iostream>
#include <fstream>
#include <set>
#include <math.h>
#include <stdlib.h>
using namespace std;

System::System():N(0), K(0), quo(0) {
	// TODO Auto-generated constructor stub
}

System::~System() {
	// return if quorum sets not initialized
	if (quo == 0)
		return;

	// else release quorum set memory
	for (uint i=0; i<N; i++)
		delete[] quo[i];
	delete[] quo;
}

void System::readConfigFile(const string &fileName) {
	ifstream in(fileName.c_str());
	if (!in) {
		cout << "\nUnable to open configuration file!";
		exit(1);
	}

	in >> N;
	if(N > 63) {
		cout << "\nToo many nodes! Limiting number to 63";
		N = 63;
	}

	K = ceil(sqrt(N));

	quo = new int* [N];
	for (uint i=0; i<N; i++) {
		quo[i] = new int [N];
		for (uint j=0; j<N; j++)
			quo[i][j] = (i == j) ? 1 : 0;
	}

	in.close();
}

void System::printQuorums() {
	cout << "\nQuorums :\n";
	for(uint i=0; i<N; i++) {
		for (uint j=0; j<N; j++)
			cout << quo[i][j] << ' ';
		cout << '\n';
	}
}

set<uint> System::checkIntersections(uint qid) {
	set<uint> aliens;
	for (uint i=0; i<N; i++) {
		bool hasIntersection = false;
		for (uint j=0; j<N; j++)
			if (quo[qid][j] == 1 && quo[i][j] == 1)
				hasIntersection = true;

		if (! hasIntersection)
			aliens.insert(i);
	}
	return aliens;
}

void System::assignQuorums() {
	for(uint i=1; i<N; i++)
		quo[0][i] = (i < K) ? 1 : -1;

	set<uint> aliens = checkIntersections(0);

	for (set<uint>::iterator it = aliens.begin(); it != aliens.end(); it++)
		cout << *it << ' ';
	cout << '\n';
}
