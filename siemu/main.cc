#include <iostream>
#include <fstream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "environment.h"

using namespace std;
#define SPEED 5
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
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    env->rom->loadROM(0x0,"invaders.h");
    env->rom->loadROM(0x800,"invaders.g");
    env->rom->loadROM(0x1000,"invaders.f");
    env->rom->loadROM(0x1800,"invaders.e");
    unsigned int omg = env->readWord(0x0014);
    cout << hex << omg;
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

