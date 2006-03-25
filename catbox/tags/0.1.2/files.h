#ifndef _FILES_H
#define _FILES_H
#endif
typedef struct
{
	FILE *file;
	char mode[4];
	char *buffer;
	int (* OpenFile) (int);	
}FileStruct;
