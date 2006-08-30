#ifndef _CGAME_H_
#define _CGAME_H_
#include <iostream>
#include <SDL/SDL.h>
#include "constants.h"
#include "cinput.h"
#include "cdisplay.h"

using namespace std;
class CGame
{
	private:
	protected:
	public:
	CDisplay *cDsp;
	static bool active;
	CGame();
	~CGame();
	void SetActive(bool mode);
	bool GetActive();
	int StartGameLoop();
	//int UpdateGameData();
	int StopGameLoop();
};
#endif