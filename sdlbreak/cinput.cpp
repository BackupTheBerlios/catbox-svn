#include "cinput.h"
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