#ifndef _CSURFACE_H_
#define _CSURFACE_H_
#include <iostream>
#include <SDL/SDL.h>
using namespace std;
class CSurface
{
	private:
	protected:
	public:
	SDL_Surface *Surface; // Shouldn't be public...
	CSurface();
	~CSurface();
};
#endif
