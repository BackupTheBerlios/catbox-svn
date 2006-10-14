#include "CSocket.h"

CSocket::CSocket()
{
	cout << "Created Socket-Instance."<<endl;
	CurrentSocket = 0;
}

CSocket::~CSocket()
{
	cout << "Deleted Socket-Instance."<<endl;
}
int CSocket::getSocket(void)
{
	return CurrentSocket;
}
int CSocket::setSocket(int Socket)
{
	CurrentSocket = Socket;
	return(0);
}
int CSocket::createSocket(int type)
{
	if(type < 1 || type > 2)
	{
		cout << "No correct type given, can't create Socket."<<endl;
		return(1);
	}
	else 
	{
		int s;
		switch(type)
		{
			case 1: //TCP
			s = socket(AF_INET,SOCK_STREAM,0);
			cout << "Using TCP: ";
			break;
			case 2: //UDP
			s = socket(AF_INET,SOCK_DGRAM,0);
			cout << "Using UDP: ";
			break;
		}
		if(s<0)
		{
			cout << "Error creating Socket. Exiting."<<endl;
			exit(1);
		}
		CurrentSocket = s;
		cout << "Socket created." << endl;
		return CurrentSocket;
	}
}
int CSocket::destroySocket()
{
	close(CurrentSocket);
	cout << "Destroyed Socket."<<endl;
	return(0);
}
int CSocket::startServer(int port)
{
	ServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerAddress.sin_port = htons(port);
	ServerAddress.sin_port = AF_INET;
	
	if(bind(CurrentSocket,(const sockaddr*)&ServerAddress,sizeof(ServerAddress)) < 0)
	{
		cout << "Failed setting up a Server on port " << port << "."<<endl;
		exit(1);
	}
	else
	{
		cout << "Set up Server on port " << port << "." << endl;
	}
	return(0);
}
int CSocket::stopServer()
{
	close(CurrentSocket);
	cout << "Stopped Server." <<endl;
	return(0);
}
int CSocket::startListening(int lengthOfQueue)
{
	if(isSocketCreated())
	{
		listen(CurrentSocket,lengthOfQueue);
		cout << "Started listening for " << lengthOfQueue << " Clients." << endl;
		return(0);
	}
	else
	{
		cout << "No Socket was created, can't start listening." << endl;
		exit(1);
	}
}
bool CSocket::isSocketCreated()
{
	if(CurrentSocket != 0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
