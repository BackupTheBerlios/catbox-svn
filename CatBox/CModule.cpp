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

