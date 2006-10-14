#ifndef CMODULE_H_
#define CMODULE_H_
#include <iostream>
#include <fstream>
#include <malloc.h>
using namespace std;
class CModule
{
protected:
public:
	ifstream ModuleFileStream;
	public:
	int *ModuleMemoryPointer;
	CModule();
	virtual ~CModule();
	int loadModule(const char *filename);
};

#endif /*CMODULE_H_*/
