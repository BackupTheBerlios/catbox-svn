#ifndef _CPADDLE_H_
#define _CPADDLE_H_
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "csurface.h"
#include "cball.h"
#include "cinput.h"
using namespace std;
class CPaddle// : public CBall
{
	private:
	protected:
	/*
	bool active;
	static int lives;
	CSurface *Surface;*/
	public:
        CSurface *Surface;
	CPaddle();
	~CPaddle();
        int xco;
        int yco;
        void updatePaddle();
	int GetLives();
	void LoadPaddle(const char* filename);
	void setXY(int xcoord,  int ycoord);
	int getX();
        void setX(int xcoord);
	int getY();
        void setY(int ycoord);
       static int addX(signed int xrel);
       static int addY(signed int yrel);
	};
#endif
