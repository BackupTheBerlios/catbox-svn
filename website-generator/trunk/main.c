#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include "files.h"
typedef char[50] string;
typedef struct
{
	string url;
	string name;
	sFile filename;
}WebSite;
int main (int argc, char **argv[])
{
	WebSite sWebSite;
	printf(_("Website-Generator 1.0"\n),);
	return (0);
}
