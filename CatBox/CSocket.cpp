#include "CSocket.h"

CSocket::CSocket()
{
}

CSocket::~CSocket()
{
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
int CSocket::createSocket()
{
	int s;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s<0)
	{
		cout << "Error creating Socket. Exiting."<<endl;
		exit(1);
	}
	CurrentSocket = s;
	return CurrentSocket;
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
