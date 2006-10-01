#include "cinput.h"
#include "cgame.h"
#include "cball.h"
#include "main.h"

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

	switch(event.type)
	{
		case SDL_KEYDOWN:
                //balltmp->running = 0;

		break;
		case SDL_QUIT:
                //balltemp->running=0;
		default:
		break;
	}
	return event.type;
}
