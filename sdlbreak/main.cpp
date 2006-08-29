#include <iostream>
#include <SDL/SDL.h>
#include "cball.h"
#include "cdisplay.h"
#include "cinput.h"
#include "cgame.h"
int CBall::lives;
int main(int argc, char *argv[])
{
	CGame *cApp;
	cApp = new CGame();
	CBall *cPlayer;
	cPlayer = new CBall();
	CDisplay *cDsp;
	cDsp = new CDisplay(XRES,YRES,BPP,SDL_HWSURFACE|SDL_DOUBLEBUF,0);
	CInput *cInp;
	cInp = new CInput(1);
	cout << cPlayer->GetLives()<<endl;
	return(0);
}







