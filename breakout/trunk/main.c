#include <stdlib.h>
#include <sys/malloc.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define XRES 800
#define YRES 600
#define DEPTH 16
#define BLOCKXRES 40
#define BLOCKYRES 15
#define BLOCKCOUNT (XRES/BLOCKXRES)*(YRES/BLOCKYRES) // X * Y 
#define BLOCKTYPES 5
#define XPADDLESTART XRES/2-40
#define YPADDLESTART YRES-60
#define XBALLSTART XPADDLESTART+20
#define YBALLSTART YPADDLESTART
#define MAXLIVES 5

FILE  *map;
SDL_Surface *screen, *stones[BLOCKTYPES], *sfcPaddle, *specials[5],*sfcTemp,*sfcBall;
SDL_Rect srcRect,destRect;
int iFPS = 100,iFrameCount = 0, iStartTime;
char *StoneMap;
typedef struct
{
	int strength;
	int x,y;
	int type;
}stone;
typedef struct
{
	int lives;
	int x,y;
	int count;
	int started;
	int horizontal;
	int vertical;
}ball;

typedef struct
{
	int mode;
	int x,y;
}paddle;


int LoadImages(int iType)
{
	SDL_RWops *rwop;
	switch(iType)
	{
	case 0:
	rwop=SDL_RWFromFile("images/paddle.png","rb");
	sfcTemp=IMG_LoadPNG_RW(rwop);
	SDL_FreeSurface(sfcPaddle);
	sfcPaddle = SDL_DisplayFormat(sfcTemp);


	break;
	case 1:
	rwop=SDL_RWFromFile("images/0.png","rb");
	sfcTemp=IMG_LoadPNG_RW(rwop);
	SDL_FreeSurface(stones[0]);
	stones[0] = SDL_DisplayFormat(sfcTemp);
	rwop=SDL_RWFromFile("images/1.png","rb");
	sfcTemp=IMG_LoadPNG_RW(rwop);
	SDL_FreeSurface(stones[1]);
	stones[1] = SDL_DisplayFormat(sfcTemp);
	rwop=SDL_RWFromFile("images/2.png","rb");
	sfcTemp=IMG_LoadPNG_RW(rwop);
	SDL_FreeSurface(stones[2]);
	stones[2] = SDL_DisplayFormat(sfcTemp);
	rwop=SDL_RWFromFile("images/3.png","rb");
	sfcTemp=IMG_LoadPNG_RW(rwop);
	SDL_FreeSurface(stones[3]);
	stones[3] = SDL_DisplayFormat(sfcTemp);
	rwop=SDL_RWFromFile("images/4.png","rb");
	sfcTemp=IMG_LoadPNG_RW(rwop);
	SDL_FreeSurface(stones[4]);
	stones[4] = SDL_DisplayFormat(sfcTemp);
	break;
	
	case 2:
	rwop=SDL_RWFromFile("images/ball.png","rb");
	sfcTemp=IMG_LoadPNG_RW(rwop);
	SDL_FreeSurface(sfcBall);
	sfcBall = SDL_DisplayFormat(sfcTemp);
	}
	return 0;
}
int CreateMap(char StMap[])
{
	int srand,trand;
	for (trand=0;trand!=BLOCKCOUNT;trand++)
	{
		srand = rand()*4;
		if(trand>=BLOCKCOUNT/2)
		{
			StMap[trand] = 0;
		}
		else
		{
		StMap[trand] = srand;
		}
		
	}

}


int ReadMap(FILE *fp, const char *filename)
{
	int c;
	int iCounter = 0;
	fp = fopen(filename,"r");	
	while ((c = fgetc(fp))!= EOF)
	{
		if(c != ',' && c != 0x0A)
		{
		StoneMap[iCounter] = c;
		putchar(c);
		iCounter += 1;
		}
	} 	
	printf("iCounter: %d\n",iCounter);
	fclose(fp);
	return iCounter;
}
int InitBall(ball bBall)
{
	bBall.lives = MAXLIVES;
	bBall.y = YPADDLESTART-20;
	
	bBall.count = 0;
	bBall.started = 0;
	bBall.horizontal = rand()*20; //10 > False, 10 < True
	bBall.vertical = rand()*20;
	return 0;
}

int CleanRect(SDL_Rect rRectangle)
{
	rRectangle.x = rRectangle.y = rRectangle.h = rRectangle.w = 0;
	return 0;
}

int UpdatePaddle(paddle pUpdPaddle, SDL_Surface *sfcUpdPaddle)
{
	if (!(pUpdPaddle.x > (XRES-(2*BLOCKXRES))))
	{
	destRect.x = pUpdPaddle.x;
	}
	else
	{
	destRect.x = (XRES-(2*BLOCKXRES));
	}
	destRect.y = pUpdPaddle.y;
	SDL_BlitSurface(sfcUpdPaddle,NULL,screen,&destRect);
	return 0;
}

int UpdateRect(SDL_Rect rRectangle, signed int iX, signed int iY, unsigned int iH, unsigned int iW)
{
	rRectangle.x = iX;
	rRectangle.y = iY;
	rRectangle.h = iH;
	rRectangle.w = iW;
	return 0;
}

int UpdateBall(ball bBall, SDL_Surface *sfcBall)
{
	int mausx,mausy;
	SDL_PumpEvents();
	SDL_GetMouseState(&mausx,&mausy);ll)
	MoveBall(&bBall);
	if(bBall.started == 0)
	{
		destRect.x = mausx;
	}
	else
	{
		destRect.x = bBall.x;
	}
	destRect.y = bBall.y;
	SDL_BlitSurface(sfcBall,NULL,screen,&destRect);
	return 0;
}
int UpdateMap(char StMap[])
{
	/*CleanRect(srcRect);
	CleanRect(destRect);*/
	UpdateRect(srcRect,0,0,40,15);
	UpdateRect(destRect,0,0,40,15);
	destRect.x = 0;
	destRect.y = 0;
	int iBlk;
	char *cTemp=NULL,cTempCpy[2];
	int iBlkType,iTemp,*iPtr;
	iBlk = 0;
	iTemp = 0;
	while(iBlk != 800)// BLOCKCOUNT)
	{ 
		cTemp= &StMap[iBlk];
		iBlkType = (int) (*cTemp-48);
		//iBlkType = atoi(cTempCpy);
		//printf("Blocktyp:%d\n",iBlkType);
//iTemp = atoi(*cTemp);
		//printf("Block-Nr.:%d\n",iBlk);
		switch(iBlkType)
		{
			default:
			break;
			case 0:
			destRect.w = stones[0]->w;
			destRect.h = stones[0]->h;
			SDL_BlitSurface(stones[0],NULL,screen,&destRect);
			//printf("Did 0! \n");

			break;
			case 1:
			destRect.w = stones[1]->w;
			destRect.h = stones[1]->h;
			SDL_BlitSurface(stones[1],NULL,screen,&destRect);
			//printf("Did 1! \n");
			break;
			case 2:
			destRect.w = stones[2]->w;
			destRect.h = stones[2]->h;
			SDL_BlitSurface(stones[2],NULL,screen,&destRect);
			//printf("Did 2! \n");
			break;
			case 3:
			destRect.w = stones[3]->w;
			destRect.h = stones[3]->h;
			SDL_BlitSurface(stones[3],NULL,screen,&destRect);
			//printf("Did 3! \n");
			break;
			case 4:
			destRect.w = stones[4]->w;
			destRect.h = stones[4]->h;
			SDL_BlitSurface(stones[4],NULL,screen,&destRect);
			//printf("Did 4! \n");
			break;

		}
		iBlk++;
		destRect.x += BLOCKXRES;
		if(destRect.y != 600)
		{
		if(destRect.x == (XRES))
		{
			destRect.x = 0;
			destRect.y += BLOCKYRES;
		}
		}
		else
		{
			destRect.y = 0;
			destRect.x = 0;
		}
	}
	return 0;
}

int MoveBall (ball bBall)
{
	return(1);
}
int main(int argc, char **argv)
{
	paddle pPaddle;
	ball bBall;
	InitBall(bBall);
	//SDL_SetColorKey(sfcBall,SDL_SRCCOLORKEY,SDL_MapRGB(sfcBall->format,254,254,254));
	StoneMap = malloc(800);
	int iDone,iTemp;
	iDone = 0;
	pPaddle.x = XPADDLESTART;
	pPaddle.y = YPADDLESTART;
	//CreateMap(StoneMap);
	iTemp = ReadMap(map,"test.txt");
	stone sStones[iTemp];
	SDL_Event event;
	atexit(SDL_Quit);
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
       		printf("Can't init SDL:  %s\n", SDL_GetError());
       		exit(1);
	}

	screen = SDL_SetVideoMode(XRES,YRES,DEPTH,SDL_SWSURFACE);
	if (screen == NULL)
	{
		printf("Can't init Video: %s\n", SDL_GetError());
		exit(1);
	} 
	LoadImages(2);
	LoadImages(1); // Nach SDL_Init! Sonst Crash! Segmentation Fault.
	LoadImages(0); 
	SDL_ShowCursor(SDL_DISABLE);
	//SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	//UpdateMap(StoneMap);
	while(!iDone)
	{
	UpdateMap(StoneMap);
	iFrameCount++;
	if(SDL_GetTicks()- iStartTime >= 1000)
	{
		printf("FPS: %d\n",iFrameCount);
		iFrameCount = 0;
		iStartTime = SDL_GetTicks();
	}
	//SDL_LockSurface(screen);
	UpdateBall(bBall,sfcBall);
	UpdatePaddle(pPaddle,sfcPaddle);
	//SDL_UnlockSurface(screen);
	SDL_Flip(screen);
	destRect.x = pPaddle.x;
	destRect.y = pPaddle.y;
	destRect.w = sfcPaddle->w;
	destRect.h = sfcPaddle->h;
	SDL_FillRect(screen,&destRect,SDL_MapRGB(screen->format,0,0,0));
      	while (SDL_PollEvent(&event)) 
       	{
		int mausx,mausy;
		SDL_PumpEvents();
           	switch(event.type) 
           	{
		case SDL_MOUSEBUTTONDOWN:
		if (bBall.started == 0)
		{
			bBall.started = 1;
		}
		else
		{
			bBall.started = 0;
		}
		break;
		case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mausx,&mausy);
		//if (event.motion.x > 0 && event.motion.x < XRES-80)
		//{

			pPaddle.x = event.motion.x;
		//}
		break;
		case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
		{
		default: 
		break;
		case SDLK_f:
		SDL_WM_ToggleFullScreen(screen);
		break;
		case SDLK_ESCAPE:
		iDone = 1;
		break;
           	case SDL_QUIT:
               	iDone = 1;
               	break;
           	}
		break;
		default:
		break;
		}
       		}
	}

	SDL_Quit();
	return 0;
}
