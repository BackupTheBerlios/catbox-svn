#include "CModule.h"

CModule::CModule()
{
	//ModuleMemoryPoiner =  malloc(0x10000);
	cout << "Created Module-Instance."<<endl;
}

CModule::~CModule()
{
	delete ModuleMemoryPointer;
	cout << "Deleted Module-Instance."<<endl;
}
int CModule::loadModule(const char *filename)
{
	ModuleMemoryPointer = (int *)  malloc(0x10000);
	char TempData;
	int FileByteCount = 0x00;
	ModuleFileStream.open(filename,ios::binary|ios::in);
	ModuleFileStream.seekg(0x00,ios::beg);
	while(ModuleFileStream.good())
	{
		ModuleFileStream.get(TempData);
		ModuleMemoryPointer[FileByteCount] = TempData;
		FileByteCount++;
	}
	cout << FileByteCount << " Bytes read for module " << filename << "."<<endl;
	ModuleFileStream.close();
	
	return(0);
}
int CModule::openModule(const char *filename)
{
	LibraryHandle = dlopen(filename,RTLD_LAZY);
	if(LibraryHandle == NULL)
	{
		cout << "Couldn't open " << filename << "." << endl;
		return(1);
	}
	cout << "Opened " << filename << " successfully." << endl;
	cout << "Loading symbol initPlugin..." << endl;
//	typedef int (*initPlugin_t)();
	dlerror(); // Reset errors
	initPlugin = (initPlugin_t) dlsym(LibraryHandle, "initPlugin");
	const char *dlsym_error = dlerror();
	if(dlsym_error)
	{
		cout << "Can't load symbol '" << INIT_PLUGIN << "': " << dlsym_error << endl;
		dlclose(LibraryHandle);
		return(1);
	}
	else
	{
		return(0);
	}	
}

int CModule::closeModule(char *filename)
{
	dlclose(LibraryHandle);
	cout << "Closed " << filename << " successfully." << endl;
	return(0);
}
