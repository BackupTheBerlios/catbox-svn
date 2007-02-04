#include <iostream>
#include <fstream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "environment.h"

using namespace std;
#define SPEED 5
#define A env->cpu->reg.a
#define F cpu->reg.psw;
#define PSW F
#define B cpu->reg.b;
#define C cpu->reg.c;
#define D cpu->reg.d;
#define H cpu->reg.H;
#define L cpu->reg.L;
#define AF cpu->af;
#define BC cpu->bc;
#define DE cpu->de;
#define HL cpu->hl;
#define SP cpu->sp;
#define PC env->cpu->pc;
#define R8(adr) cpu->memory[((adr)>0x1fff)?(adr)&0x1fff | 0x2000:adr]
#define R16(adr) (R8((adr) + 1)<<8 | (R8(adr)))
#define W8(adr,val) if (adr>0x1fff) cpu->memory[((adr)&0x1fff) | 0x2000]=v
#define PUSH16(val) SP-=2; W8(SP,(val)&0xff) | W8(SP+1,(val)>>8 & 0xff)
#define POP16() R16(SP);SP+=2
#define JUMP() PC=R16(PC);
#define CALL() PUSH16(PC+2); JUMP(); // Rücksprung-Adresse auf den Stack
SDL_Surface *screen;
SDL_Surface *wall;
static const unsigned char cycle_table[0x100]={
	4, 10,7, 5, 5, 5, 7, 4, 0, 10,7, 5, 5, 5, 7, 4,
	0, 10,7, 5, 5, 5, 7, 4, 0, 10,7, 5, 5, 5, 7, 4,
	0, 10,16,5, 5, 5, 7, 4, 0, 10,16,5, 5, 5, 7, 4,
	0, 10,13,5, 10,10,10,4, 0, 10,13,5, 5, 5, 7, 4,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 5,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	5, 10,10,10,11,11,7, 11,5, 10,10,0, 11,17,7, 11,
	5, 10,10,10,11,11,7, 11,5, 0, 10,10,11,0, 7, 11,
	5, 10,10,18,11,11,7, 11,5, 5, 10,4, 11,0, 7, 11,
	5, 10,10,4, 11,11,7, 11,5, 5, 10,4, 11,0, 7, 11
};


int main(int argc, char** argv) 
{
    using namespace std;
    
    unsigned char *mem = new unsigned char[0x4000];
    tEnvironment *env;
    env = new tEnvironment();
    //env->cpu->executeCycles(2);
   // memory->memory = mem;                                                                                                                                                                   "

   // cpu->executeCycles(2);

 //   printf("%d",R8());
    // rom->memory = 20;
   /* printf("pclo:%0x",cpu->pclo);
    printf("pchi:%0x",cpu->pchi);*/
    SDL_Rect srect,drect;
    SDL_Event event;
    SDL_Surface *buffer;
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    atexit(SDL_Quit);
    env->rom->loadROM(0x0,"invaders.h");
    env->rom->loadROM(0x800,"invaders.g");
    env->rom->loadROM(0x1000,"invaders.f");
    env->rom->loadROM(0x1800,"invaders.e");
 //   env->readByte (env->cpu->reg->pc);
   // env->readByte(PC);
    int running=1;
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        cout << "Can't initialize SDL" << endl;
        exit(-1);
    }
    buffer = SDL_SetVideoMode(800,600,16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(buffer == NULL)
    {
            fprintf(stderr,"Fehler: %s", SDL_GetError());
    }
    
    
    SDL_ShowCursor(0);
    
    while(!running==0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                
                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_f:
                        SDL_WM_ToggleFullScreen(buffer);
                        break;
                    case SDLK_ESCAPE:
                        running=0;
                        break;
                    default:
                        break;
                }
                break;
                case SDL_QUIT:
                    running=0;
                    break;
                default:
                    break;
            }
        }
    }
    
    return (EXIT_SUCCESS);
}

