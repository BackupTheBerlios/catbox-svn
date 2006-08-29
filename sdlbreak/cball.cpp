#include "cball.h"
#include "constants.h"
CBall::CBall()
{
	lives=LIVES;
	cout << "New Ball created." << endl;
}
CBall::~CBall()
{
	cout << "Ball destroyed." << endl;
}
int CBall::GetLives()
{
	return lives;
}