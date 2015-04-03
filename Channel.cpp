/*
 * Channel.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: Ravish
 */

#include "Channel.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

Channel::Channel(bool server, sockaddr_in saddr, sockaddr_in caddr, int portno):
	isServer(server),
	socketAccept(0),
	socketBind(0),
	socketConnect(0),
	servAddr(saddr),
	cliAddr(caddr),
	portNo(portno) {

	if(isServer)
		openChannel();
	else
		connectChannel();
}

Channel::~Channel() {
	if(isServer) {
		close(socketAccept);
		close(socketBind);
	}
	else
		close(socketConnect);
}

void Channel::openChannel() {
	socketBind = socket(AF_INET, SOCK_STREAM, 0);
	if (socketBind < 0) {
		cout << "Error creating socket!";
		return;
	}

	if (bind(socketBind, (sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
		cout << "Error binding socket to server address";
		return;
	}

	listen (socketBind, 25);

	unsigned int cliLen = sizeof(cliAddr);
	socketAccept = accept(socketBind, (sockaddr *) &cliAddr, &cliLen);
	if(socketAccept < 0) {
		cout << "Error accepting socket to client!";
		return;
	}

	cout << "Connection successful" << endl;
}

void Channel::nonBlock(int &socket) {
	if( fcntl(socket, F_SETFL, fcntl(socket, F_GETFL, 0) | O_NONBLOCK) == -1) {
		cout << "Unable to make socket non-blocking!";
		exit(1);
	}
}

void Channel::connectChannel() {
	socketConnect = socket(AF_INET, SOCK_STREAM, 0);
	if (socketConnect < 0) {
		cout << "Error creating socket!";
		return;
	}

	if (connect(socketConnect,(sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
		cout << "Error connect to server!";
		return;
	}

	cout << "Connection successful" << endl;
}

void Channel::readFromChannel (char buffer[]) {
	bzero(buffer, BUFSIZE);
	int *socket = 0;
	if (isServer)
		socket = &socketAccept;
	else
		socket = &socketConnect;

	if (read(*socket, (void *)buffer, BUFSIZE-1) < 0)
		cout << "ERROR reading from socket" << endl;
}

void Channel::writeToChannel (char buffer[]) {
	int *socket = 0;
	if (isServer)
		socket = &socketAccept;
	else
		socket = &socketConnect;

	if (write(*socket, (void *)buffer, BUFSIZE) < 0)
		 cout << "ERROR writing to socket" << endl;
}
