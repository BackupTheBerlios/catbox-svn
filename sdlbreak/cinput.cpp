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
void CInput::ChangeDeviceType(int devtype)
{
	type = devtype;
}
int CInput::UpdateInput(SDL_Event &event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		CGame::active=0;
		break;
		case SDL_QUIT:
		CGame::active=0;
		default:
		break;
	}
	return event.type;
}