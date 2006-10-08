#ifndef _CPADDLE_H_
#define _CPADDLE_H_
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "csurface.h"
#include "cball.h"
#include "cinput.h"
using namespace std;
class CPaddle : public CBall
{
	private:
	protected:
	/*
	bool active;
	static int lives;
	CSurface *Surface;*/
	public:
     //   CSurface *Surface;
	CPaddle();
	~CPaddle();
        static int xco;
        static int yco;
        void updatePaddle();
	int GetLives();
	void setXY(int xcoord,  int ycoord);
	int getX();
        void setX(int xcoord);
	int getY();
        void setY(int ycoord);
        int addX(signed int xrel);
        int addY(signed int yrel);
};
#endif
