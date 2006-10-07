#include "cpaddle.h"
int CPaddle::xco;
int CPaddle::yco;
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
void CPaddle::setXY(int xcoord,int ycoord)
{
	CPaddle::xco=xcoord;
	CPaddle::yco=ycoord;
}
void CPaddle::setX(int xcoord)
{
    CPaddle::xco=xcoord;
}
void CPaddle::setY(int ycoord)
{
    yco=ycoord;
}
int CPaddle::getX()
{
	return CPaddle::xco;
}
int CPaddle::getY()
{
	return CPaddle::yco;
}
int CPaddle::addX(signed int xrel)
{
    CPaddle::xco += xrel;
    return (0);
}
int CPaddle::addY(signed int yrel)
{
   
    return(0);
}
