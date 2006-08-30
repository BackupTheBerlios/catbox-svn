#include "cgame.h"
 bool CGame::active;
CGame::CGame()
{
	
	active = true;
	cout << "New Game started." << endl;
}
CGame::~CGame()
{
	cout << "Game quitted." << endl;

}
void CGame::SetActive(bool mode)
{
	active = mode;
	cout << "Game activity changed to: " << mode << endl;
}
bool CGame::GetActive()
{
	return active;
}
int CGame::StartGameLoop()
{
	SDL_Event event;
	SetActive(true);
	while (active)
	{
		while(SDL_PollEvent(&event))
		{
			CInput *cInp;
			cInp = new CInput(1);
			
			cout<<(cInp->UpdateInput(event))<<endl;
			delete cInp;
		}
		
	}
	return (0);
}
int CGame::StopGameLoop()
{
	SetActive(false);
	return (0);
}
