#include <iostream>
#include <cstdio>
#include "socket.h"
#include "network.h"
using namespace std;
int CSocket::InstanceCount = 0;
int CNetwork::InstanceCount = 0;
int main(int argc , char **argv)
{
	CNetwork cNet;
	CSocket cS(SOCK_STREAM);
	cout << argc;
	char *argument=argv[0]+2;
	cout << endl;
	cout << "Executable is named <<" << argument << ">> and uses the following arguments:"<< endl;

	for(int i=1;i<argc;i++)
	{
		char *arguments = argv[i];
		
		cout << arguments << "\n";
	}
	if (argc == 1)
	{	
		cout << "No Arguments delivered.\n";	
	}
	
	return(0);
}