#ifndef _CBALL_H_
#define _CBALL_H_
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "csurface.h"
#include "cdisplay.h"
using namespace std;

class CBall
{
	private:
	protected:
	int ux,uy;
	bool active;
	static int lives;
	
       
	public:
        //CSurface *Surface;
        SDL_Surface *Surface;
        SDL_Rect srect,drect;
	CBall();
	~CBall();
        static int running;
	int GetLives();
	void LoadIMG(const char* filename);
        virtual void Blit(SDL_Surface &sur, SDL_Rect &srcrect);//, SDL_Rect &dstrect);
};
#endif
