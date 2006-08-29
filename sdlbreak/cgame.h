#ifndef _CGAME_H_
#define _CGAME_H_
#include <iostream>
#include <SDL/SDL.h>
#include "constants.h"
using namespace std;
class CGame
{
	private:
	protected:
	bool active;
	public:
	CGame();
	~CGame();
	void SetActive(bool mode);
	bool GetActive();
};
#endif