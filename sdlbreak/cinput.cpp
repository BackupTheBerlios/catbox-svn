#include "cinput.h"
#include "cgame.h"
CInput::CInput(int devtype)
{
	type = devtype;
	cout << "Input Device Type " << devtype << " created." << endl;
}
CInput::~CInput()
{
	cout << "Input Device Type " << type << " deleted." << endl;
}
void CInput::changeDeviceType(int devtype)
{
	type = devtype;
}
int CInput::updateInput(SDL_Event &event)
{
    
    SDL_Event event;
	switch(event.type)
	{
		case SDL_KEYDOWN:
                running = 0;

		break;
		case SDL_QUIT:
                running=0;
		default:
		break;
	}
	return event.type;
}
