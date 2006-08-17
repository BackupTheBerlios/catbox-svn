#include "client.h"

CClient::CClient()
{
    cout << "New connection found"<<endl;
}
CClient::~CClient()
{
    cout << "Connection closed"<<endl;
}