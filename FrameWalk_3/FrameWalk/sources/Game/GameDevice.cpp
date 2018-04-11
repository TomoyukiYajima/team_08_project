#include "GameDevice.h"
#include "../Utility/Resource/Graphic/Graphics3D/Graphics3D.h"

GameDevice::GameDevice(
	int width, int height, 
	float rate, int windowMode,
	int colorBitDepth)
{
	//SetWindowIconID(IDI_MYICON); // �A�C�R���̐ݒ�(���ݖ��g�p)
	// �E�B���h�E�g�̕����ݒ�
	SetMainWindowText("Game");
	// �O���t�B�b�N���[�h�̐ݒ�
	SetGraphMode(width, height, colorBitDepth);
	// �E�B���h�E���[�h�̐ݒ�
	ChangeWindowMode(windowMode);
	//ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	// �`��䗦�̐ݒ�
	SetWindowSizeExtendRate(rate);
	//SetBackgroundColor(0, 0, 0);

	//if (DxLib_Init() == -1)		// �c�w���C�u��������������
	//{
	//	return -1;			// �G���[���N�����璼���ɏI��
	//}

	// DXLib�̏���������
	if (DxLib_Init() == -1) DxLib_End();//�G���[���N������I��

	//SetDrawScreen(DX_SCREEN_BACK);
	Graphics3D::initialize();
}

void GameDevice::flip()
{
	ScreenFlip();
}
