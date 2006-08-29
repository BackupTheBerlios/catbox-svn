#ifndef _CBALL_H_
#define _CBALL_H_
#include <iostream>
#include <SDL/SDL.h>
using namespace std;
class CBall
{
	private:
	protected:
	int x,y;
	bool active;
	static int lives;
	public:
	CBall();
	~CBall();
	int GetLives();
};
#endif