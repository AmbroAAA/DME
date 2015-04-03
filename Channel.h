/*
 * Channel.h
 *
 *  Created on: Mar 31, 2015
 *      Author: Ravish
 */

#ifndef SRC_CHANNEL_H_
#define SRC_CHANNEL_H_

#include <netinet/in.h>
#include <pthread.h>

const unsigned int BUFSIZE = 256;

class Channel {

	bool isServer;			//< channel server object if this flag is set
	int socketAccept;		//< socket file descriptor to accept connection at server
	int socketBind;			//< socket file descriptor to bind socket to server
	int socketConnect;		//< socket file descriptor to connect to server at client
	sockaddr_in servAddr;	//< server address
	sockaddr_in cliAddr;	//< client address
	int portNo;				//< common port number on which both parties will make a socket connection

	pthread_t channelThread;

	void openChannel();		//< called by server
	void connectChannel();	//< called by client
	void nonBlock(int &); 	//< make a socket non-blocking
public:
	Channel(bool, sockaddr_in, sockaddr_in, int);
	void readFromChannel(char []);
	void writeToChannel(char []);
	virtual ~Channel();
};

#endif /* SRC_CHANNEL_H_ */
