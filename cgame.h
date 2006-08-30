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
	public:
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