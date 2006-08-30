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
	CGame *cTmp;
	cTmp = new CGame();
	switch(event.type)
	{
		case SDL_KEYDOWN:
	
		cTmp->SetActive(0);
		break;
		case SDL_QUIT:
		cTmp->SetActive(0);
		default:
		break;
	}
	delete cTmp;
	return event.type;
}