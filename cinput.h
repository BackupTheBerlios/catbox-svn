#ifndef _CINPUT_H_
#define _CINPUT_H_
#include <iostream>
#include <SDL/SDL.h>
#include "constants.h"
using namespace std;
class CInput
{
	private:
	protected:
	int type; // 0 = Undefined, 1 = Keyboard, 2 = Mouse, 3 = Network, 4 = Undefined
	public:
	CInput(int devtype);
	~CInput();
	void ChangeDeviceType(int devtype);
	int UpdateInput(SDL_Event &event);
};
#endif