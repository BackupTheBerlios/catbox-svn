#include <iostream>
#include <SDL/SDL.h>
#include "cball.h"
#include "cdisplay.h"
#include "cinput.h"
#include "cgame.h"
#include "cpaddle.h"
int CBall::lives;
int main(int argc, char *argv[])
{
	CGame *cApp;
	cApp = new CGame();
	CBall *cPlayer;
	cPlayer = new CBall();
	/*CDisplay *cDsp;
	cDsp = new CDisplay(XRES,YRES,BPP,SDL_HWSURFACE|SDL_DOUBLEBUF,0);*/
	CInput *cInp;
	cInp = new CInput(1);
	CPaddle *cPdl;
	cPdl = new CPaddle();
	cout << cPlayer->GetLives()<<endl;
	cPlayer->LoadIMG("images/cball.bmp");
	cPdl->LoadPaddle("images/paddle.bmp");
	cPdl->SetXY(10,20);
	cout << cPdl->GetX() << " " << cPdl->GetY();
	cApp->StartGameLoop();
	return(0);
}







