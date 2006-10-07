
#include "cball.h"
#include "constants.h"
CBall::CBall()
{
        running=1;
	lives=LIVES;
	cout << "New Ball created." << endl;
	Surface = new CSurface();
        
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
        Surface->Surface = SDL_DisplayFormat(temp);
}


