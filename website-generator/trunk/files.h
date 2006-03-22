#ifndef _FILES_H
#define _FILES_H
#endif


typedef struct 
{
	FILE *file;
	char *cPtrFilename;
	char filename;
	char mode[4];
	char *buffer;
	int (* OpenFile)(int); 
	int (* ReadFile)(int);
	int (* Close)(int);		
}FileStruct;
