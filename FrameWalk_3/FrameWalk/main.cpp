//#include "DxLib.h"
#include "sources/Game/GameManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return GameManager().run();
}