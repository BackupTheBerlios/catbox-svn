#include <iostream>
#include <SDL/SDL.h>
#include "cball.h"
#include "cdisplay.h"
int CBall::lives;
int main(int argc, char *argv[])
{
	CBall *cPlayer;
	cPlayer = new CBall();
	CDisplay *cDsp;
	cDsp = new CDisplay(640,480,0,SDL_HWSURFACE|SDL_DOUBLEBUF,0);
	cout << cPlayer->GetLives()<<endl;
	return(0);
}







