#include <iostream>
#include <SDL/SDL.h>
#include "cball.h"
#include "cdisplay.h"
#include "constants.h"
#include "cinput.h"
#include "cpaddle.h"
int CBall::lives; 
int updateGameData();
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
	cPlayer->LoadIMG("images/ball.png");
	cPdl->LoadPaddle("images/paddle.png");
        cPdl->setY((YRES/3)*2);
  
	cPdl->setX((XRES/2)-cPdl->Surface->Surface->w);
 	cout << cPdl->getX() << " " << cPdl->getY();
	while (CBall::running)
	{
            

            updateGameData();
            SDL_Flip(cDsp->screen);  	
	}
	return(0);
}

int updateGameData()
{
    	SDL_Event event;
    	while(SDL_PollEvent(&event))
	{
		CInput *cInp;
		cInp = new CInput(1);
			
		cout<<(cInp->updateInput(event))<<endl;
		delete cInp;
	}
    return (0);
}




