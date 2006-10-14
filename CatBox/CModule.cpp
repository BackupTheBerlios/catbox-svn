#include "CModule.h"

CModule::CModule()
{
	cout << "Created Module-Instance."<<endl;
}

CModule::~CModule()
{
	cout << "Deleted Module-Instance."<<endl;
}
int CModule::loadModule(const char *filename)
{
	return(0);
}

