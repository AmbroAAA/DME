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

	bool isServer;
	int socketAccept;
	int socketBind;
	int socketConnect;
	sockaddr_in servAddr;
	sockaddr_in cliAddr;
	int portNo;

	pthread_t channelThread;
	char channelBuffer[BUFSIZE];

	void openChannel();
	void connectChannel();

public:
	Channel(bool, sockaddr_in, sockaddr_in, int);
	void readFromChannel();
	void writeToChannel(char []);
	void channelManager();
	virtual ~Channel();
};

#endif /* SRC_CHANNEL_H_ */
