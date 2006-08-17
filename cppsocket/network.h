#ifndef _NETWORK_H_
#define _NETWORK_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;
	/*enum ServerMode
	{
		SERVER_MODE = 0,
		CLIENT_MODE= 1
	};*/
class CNetwork
{
	private:
	int Mode;
	static int InstanceCount;
	protected:

	public:
	int iNet;
	void Connect(const char* cHostname, int iPort);
	CNetwork();
	~CNetwork();	
};
#endif