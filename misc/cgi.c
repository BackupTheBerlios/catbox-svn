/* Copyright Norman Mapes 2006
 * GNU GPL v2
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct { //kv = key=value
	char **k;	//key
	char **v;	//value
	int elements;	//nelements
} keys ={0};


getmemory()
{
	keys.elements=0;
	keys.k=malloc(100*sizeof(char*));
	keys.v=malloc(100*sizeof(char*));
}

void associate(char *key, char *value)
{
	keys.k[keys.elements] = malloc(strlen(key));
	keys.v[keys.elements] = malloc(strlen(value));
	strcpy(keys.k[keys.elements], key);
	strcpy(keys.v[keys.elements], value);
	keys.elements++;
}

char *value(char *key)
{
	int i=0;
	while (i<keys.elements)
		if (!strcmp(key,keys.k[i++]))
			return keys.v[--i];
}

makevalues()
{
	char c, decode[3]={0};
	char key[1024];
	char value[4096];
	int in_key=1;
	int i=0;
	while (( c = getchar()) != EOF)
	{
		if ( c == '&' || c == ';')
		{
			in_key=1;
			value[i]='\0';
			i=0;
			associate(key, value);
			continue;
		}
		if (c == '=')
		{
			in_key=0;
			key[i]='\0';
			i=0;
			continue;
		}
		if (in_key)
		{
			if (i>1024)
			{
				phtml("Name too large");
				exit(-1);
			}
			key[i++] = c;
		}
		else
		{
			if (i>4096)
			{
				phtml("Value too large");
				exit(-1);
			}
			if (c=='%')
			{
				decode[0]=getchar();
				decode[1]=getchar();
				c = strtol(decode,NULL,16);
			}
			if (c=='+')
				c = ' ';
			value[i++] = c;
		}
	}
	associate(key, value);

}

int html_header(char *title)
{
	printf(
		"<html>\n"
		"<head><title>%s</title></head>\n"
		"<body>\n"
	      , title
	      );
	return 0;
}

phtml(char *string)
{
	puts("<br>");
	puts(string);
	puts("<br>");
}


int main(int ac, char**av)
{
	getmemory();
	makevalues();
	setvbuf(stdout,NULL,_IONBF,0);
	printf("Content-Type: text/html\n\n");
	html_header("John's C CGI");
	printf("<h1>Hi</h1>");
		
	printf("<br>CONTENT_LENGTH %s<br>", getenv("CONTENT_LENGTH"));
	printf("<br>CONTENT_TYPE %s<br>", getenv("CONTENT_TYPE"));
	puts(value("textarea"));
	

	fflush(stdout);
	return 0;
}
