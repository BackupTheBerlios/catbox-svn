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
	cPdl->LoadIMG("images/paddle.png");
        cPdl->setY((YRES/3)*2);
	cPdl->setX((XRES/2));
 	cout << cPdl->getX() << " " << cPdl->getY();
        cPdl->srect.w = cPdl->Surface->w;
        cPdl->srect.h = cPdl->Surface->h;
        cPdl->srect.x = cPdl->srect.y = 0;
        cPdl->drect.w = cPdl->Surface->w;
        cPdl->drect.h = cPdl->Surface->h;
        
	while (CBall::running)
	{
            cPdl->drect.x = cPdl->xco;
            cPdl->drect.y = cPdl->yco;
    	SDL_Event event;
    	while(SDL_PollEvent(&event))
	{
		CInput *cInp;
		cInp = new CInput(1);
			
		cout<<(cInp->updateInput(event))<<endl;
		delete cInp;
	}
            cPdl->Blit(*cDsp->Surface,cPdl->srect);//,&cPdl->drect);
            updateGameData();
            SDL_Flip(cDsp->Surface);  	
	}
	return(0);
}

int updateGameData()
{

    return (0);
}




