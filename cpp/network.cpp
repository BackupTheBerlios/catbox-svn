#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include "network.h"
using namespace std;
int network::createSocket()
{
	sockfd2 = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd2 == -1)
	{
		printf("Error happened when creating socket. OMG! We we'll all die!!\n");
	}
	printf("Socket properly created.\n");
	return (sockfd2);
}
network::network()
{
}
network::~network()
{
}