#include "cball.h"
#include "constants.h"
CBall::CBall()
{
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