/*
 * System.h
 *
 *  Created on: Mar 31, 2015
 *      Author: Ravish
 */

#ifndef SRC_SYSTEM_H_
#define SRC_SYSTEM_H_

#include <iostream>
#include <set>
using namespace std;

typedef unsigned int uint;

class System {
	uint N, K;

	set<uint> checkIntersections(uint qid);
public:

	int **quo;

	System();
	void readConfigFile(const string &);
	void assignQuorums();
	void printQuorums();

	virtual ~System();
};

#endif /* SRC_SYSTEM_H_ */
