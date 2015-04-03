/*
 * Master.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: Ravish
 */

#include "System.h"
#include "Channel.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

sockaddr_in getAddressObject(char * ipv4, unsigned short port) {
	in_addr iaddr;
	sockaddr_in addr;
	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;

	if(inet_aton(ipv4, &iaddr) == -1) {
		cout << "Invalid IPv4 address!";
		exit(1);
	}

	addr.sin_addr.s_addr = iaddr.s_addr;
	addr.sin_port = htons(port);

	return addr;
}

int main(int argc, char *argv[]) {

	if (argc != 5) {
		cout << "Invalid command line!" << endl;
		cout << "Usage for server: ./<binary> <server IPv4> <client IPv4> <port No> 1" << endl;
		cout << "Usage for client: ./<binary> <server IPv4> <client IPv4> <port No> 0" << endl;
		exit(1);
	}

	sockaddr_in saddr, caddr;
	saddr = getAddressObject(argv[1], atoi(argv[3]));
	caddr = getAddressObject(argv[2], atoi(argv[3]));
	bool serv = ((argv[4][0] == '1') ? true : false);
	Channel ch(serv, saddr, caddr, atoi(argv[3]));

	char buf[BUFSIZE];

	if (serv) {
		cout << "Input : ";
		cin >> buf;
		ch.writeToChannel(buf);
	}
	else {
		ch.readFromChannel(buf);
		cout << "Output : " << buf << endl;
	}


	//System sys;
	//sys.readConfigFile("resources/Config1.conf");
	//sys.assignQuorums();
	//sys.printQuorums();
	return 0;
}
