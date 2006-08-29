#include <iostream>
#include <SDL/SDL.h>
#include "cdisplay.h"
int main(int argc, char *argv[])
{
	CDisplay *cDsp;
	cDsp = new CDisplay(640,480,0,SDL_HWSURFACE|SDL_DOUBLEBUF,0);
	return(0);
}







