#include "cgame.h"
CGame::CGame()
{
	active = true;
	cout << "New Game started." << endl;
}
CGame::~CGame()
{
	active = false;
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