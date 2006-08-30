#include "cpaddle.h"
CPaddle::CPaddle()
{
	cout << "New Paddle created." << endl;
}
CPaddle::~CPaddle()
{
	cout << "CPaddle destroyed." << endl;
}
void CPaddle::LoadPaddle(const char *filename)
{
	Surface->Surface = SDL_LoadBMP(filename);	
}
void CPaddle::SetXY(int xcoord,int ycoord)
{
	x=xcoord;
	y=ycoord;
}
int CPaddle::GetX()
{
	return x;
}
int CPaddle::GetY()
{
	return y;
}