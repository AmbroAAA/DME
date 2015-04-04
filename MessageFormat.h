#pragma once

/*=======================Message Types========================*/
#define REQUEST_FINAL 0
#define REQUEST_PARTIAL 1
#define HAVE_TOKEN 2
#define RELEASE 3
#define SEND_TOKEN 4
#define RREQUEST 5
#define SETTLE 6
#define UPDATE_HOLD_TOKEN 7
#define UPDATE_LOSE_TOKEN 8

#define MAX_IP_LENGTH 16

/*=====================Message Packet========================*/
struct Packet
{
  int TYPE;              //Message Type
  int senderID;          //This message`s senderID
  
}
