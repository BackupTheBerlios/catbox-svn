#ifndef _CBALL_H_
#define _CBALL_H_
#include <iostream>
#include <SDL/SDL.h>
#include "csurface.h"
using namespace std;
class CBall
{
	private:
	protected:
	int x,y;
	bool active;
	static int lives;
	CSurface *Surface;
	public:
	CBall();
	~CBall();
	int GetLives();
};
#endif