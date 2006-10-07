#include "cinput.h"
int CBall::running=1;
CInput::CInput(int devtype)
{
	type = devtype;
	cout << "Input Device Type " << devtype << " created." << endl;
}
CInput::~CInput()
{
	cout << "Input Device Type " << type << " deleted." << endl;
}

int CInput::updateInput(SDL_Event &event)
{
    CPaddle *cTempPaddle = new CPaddle();    

	switch(event.type)
	{
		case SDL_KEYDOWN:
                CBall::running=0;
                   
		break;
                case SDL_MOUSEMOTION:
                cTempPaddle->addX(event.motion.xrel);
                break;
		case SDL_QUIT:
                CBall::running=0;
		default:
		break;
	}
	return event.type;
}
