//#include "DxLib.h"
#include "sources/Game/GameManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return GameManager().run();
}