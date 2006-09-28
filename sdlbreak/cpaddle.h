#ifndef _CPADDLE_H_
#define _CPADDLE_H_
#include <iostream>
#include <SDL/SDL.h>
#include "csurface.h"
#include "cball.h"
using namespace std;
class CPaddle : public CBall
{
	private:
	protected:
	/*int x,y;
	bool active;
	static int lives;
	CSurface *Surface;*/
	public:
	CPaddle();
	~CPaddle();
	int GetLives();
	void LoadPaddle(const char* filename);
	void SetXY(int xcoord,  int ycoord);
	int GetX();
	int GetY();
	};
#endif
        
        