#ifndef CMODULE_H_
#define CMODULE_H_
#include <iostream>
#include <fstream>
using namespace std;
class CModule
{
protected:
public:
	ifstream ModuleFilestream;
	CModule();
	virtual ~CModule();
	int loadModule(const char *filename);
};

#endif /*CMODULE_H_*/
