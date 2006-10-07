#ifndef _CBALL_H_
#define _CBALL_H_
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "csurface.h"
#include "cpaddle.h"
using namespace std;

class CBall
{
	private:
	protected:
	int ux,uy;
	bool active;
	static int lives;
	CSurface *Surface;
	public:
	CBall();
	~CBall();
        static int running;
	int GetLives();
	void LoadIMG(const char* filename);
};
#endif
