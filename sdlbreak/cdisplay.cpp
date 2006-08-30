#include "cdisplay.h"
CDisplay::CDisplay()
{
	cout << "New Display created." << endl;
}
CDisplay::CDisplay(int x,int y,int bpp, unsigned int flags, bool fullscreen)
{
	cout << "New Display created." << endl;
	SetVideoMode(x,y,bpp,flags,fullscreen);
}
CDisplay::~CDisplay()
{
	cout <<  "Display deleted." << endl;
}
int CDisplay::SetVideoMode(int x,int y, int bpp, unsigned int flags,bool fullscreen)
{
	if(fullscreen)
	{
		flags |= SDL_FULLSCREEN;
	}
	screen = SDL_SetVideoMode(x,y,bpp,flags);
	if(!screen)
	{
		cout << "Can't set Video Mode. Quitting..." << endl;
		exit(1);
	}
	return (0);
}

SDL_Surface* CDisplay::GetSurface()
{
	return screen;
}