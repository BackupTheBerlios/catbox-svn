#ifndef _CDISPLAY_H_
#define _CDISPLAY_H_
#include <iostream>
#include <SDL/SDL.h>
using namespace std;
class CDisplay
{
	private:
	protected:
	int x;
	int y;
	int bpp;
	public:
	SDL_Surface *Surface;
	int SetVideoMode(int x,int y, int bpp, unsigned int flags, bool fullscreen);
	CDisplay();
	CDisplay(int x,int y,int bpp, unsigned int flags, bool fullscreen);
	~CDisplay();
	SDL_Surface* GetSurface();
};
#endif
