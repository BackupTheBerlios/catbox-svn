#ifndef _FILES_H
#define _FILES_H
#endif
typedef struct FileStruct
{
	FILE *file;
	char *cPtrFilename
	char filename
	char mode[4];
	char *buffer;
	int_8t (*OpenFile)(int_8t)(const char); 
	int_8t (*ReadFile)(int_8t)(int_16t);
	int_8t (*Close)(int_8t);		
};
