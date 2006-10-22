// SAMBA Plugin for CatBox
#include <stdio.h>
char *PluginName = "SAMBA";
char *Version = "0.1";
int initPlugin()
{
	printf("Initialized %s %s.",PluginName,Version);
	return(0);
}
