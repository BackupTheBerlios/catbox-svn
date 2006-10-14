#ifndef CMODULE_H_
#define CMODULE_H_

class CModule
{
protected:
	ifstream ModuleFile;
public:
	CModule();
	virtual ~CModule();
	loadModule(const char *filename);
};

#endif /*CMODULE_H_*/
