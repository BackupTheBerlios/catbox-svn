#ifndef _FILES_H
#define _FILES_H
#endif
typedef struct
{
	FILE *file=NULL;
	char mode[4];
	char *buffer=NULL;
	int_8t (_stdcall* ReadFile)(int_8t);		
}FileStruct;
