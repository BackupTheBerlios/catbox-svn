#include <iostream>
#include <SDL/SDL.h>
#include "cball.h"
#include "cdisplay.h"
#include "constants.h"
#include "cinput.h"
#include "cpaddle.h"
int CBall::lives; 

int main(int argc, char *argv[])
{
     
	CBall *cPlayer;
	cPlayer = new CBall();
	CDisplay *cDsp;
	cDsp = new CDisplay(XRES,YRES,BPP,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_ANYFORMAT,0);
	CInput *cInp;
	cInp = new CInput(1);
	CPaddle *cPdl;
	cPdl = new CPaddle();
	cout << cPlayer->GetLives()<<endl;
	cPlayer->LoadIMG("irmages/cball.bmp");
	cPdl->LoadPaddle("images/paddle.bmp");
	cPdl->SetXY(10,20);
	cout << cPdl->GetX() << " " << cPdl->GetY();
	SDL_Event event;
	while (CBall::running)
	{
		while(SDL_PollEvent(&event))
		{
			CInput *cInp;
			cInp = new CInput(1);
			
			cout<<(cInp->updateInput(event))<<endl;
			delete cInp;
		}
	SDL_Flip(cDsp->screen);  	
	}
	return(0);
}






