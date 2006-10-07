#include "cpaddle.h"
CPaddle::CPaddle()
{
	cout << "New Paddle created." << endl;
}
CPaddle::~CPaddle()
{
	cout << "CPaddle destroyed." << endl;
}
void CPaddle::updatePaddle()
{
    
}
void CPaddle::LoadPaddle(const char *filename)
{
	Surface->Surface = IMG_Load("images/paddle.png");	
}
void CPaddle::setXY(int xcoord,int ycoord)
{
	xco=xcoord;
	yco=ycoord;
}
void CPaddle::setX(int xcoord)
{
    xco=xcoord;
}
void CPaddle::setY(int ycoord)
{
    yco=ycoord;
}
int CPaddle::getX()
{
	return xco;
}
int CPaddle::getY()
{
	return yco;
}
int CPaddle::addX(signed int xrel)
{
    xco += xrel;
    return (0);
}
int CPaddle::addY(signed int yrel)
{
   
    return(0);
}
