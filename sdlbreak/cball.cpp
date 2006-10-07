
#include "cball.h"
#include "constants.h"
CBall::CBall()
{
        running=1;
	lives=LIVES;
	cout << "New Ball created." << endl;
	//Surface = new CSurface();
        
}
CBall::~CBall()
{
	cout << "Ball destroyed." << endl;
}
int CBall::GetLives()
{
	return lives;
}
void CBall::LoadIMG(const char *filename)
{
        SDL_Surface *temp;
	temp = IMG_Load(filename);
        Surface = SDL_DisplayFormat(temp);
}
void CBall::Blit(SDL_Surface &surf, SDL_Rect &srcrect, SDL_Rect &dstrect)
{
    SDL_BlitSurface(Surface,&srect,&surf,&drect);
}