#ifndef _NETWORK_H_
#define _NETWORK_H_
#include <iostream>
#include <sys/types.h>
using namespace std;
class CNetwork
{
	private:
	static int InstanceCount;
	protected:
	enum ServerMode
	{
		SERVER_MODE = 0,
		CLIENT_MODE= 1
	};
	public:
	void CNetwork::Connect(const char* cHostname, int iPort);
	CNetwork();
	~CNetwork();	
};
#endif