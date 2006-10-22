#ifndef CMODULE_H_
#define CMODULE_H_
#include <iostream>
#include <fstream>
#include <malloc.h>
#include <dlfcn.h>
using namespace std;
class CModule
{
protected:
void* LibraryHandle;
public:
	ifstream ModuleFileStream;
	public:
	int *ModuleMemoryPointer;
	CModule();
	virtual ~CModule();
	int loadModule(const char *filename);
	int openModule(const char *filename);
	int closeModule(char *filename);
};

#endif /*CMODULE_H_*/
