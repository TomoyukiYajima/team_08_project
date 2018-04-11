#include "GameDevice.h"
#include "../Utility/Resource/Graphic/Graphics3D/Graphics3D.h"

GameDevice::GameDevice(
	int width, int height, 
	float rate, int windowMode,
	int colorBitDepth)
{
	//SetWindowIconID(IDI_MYICON); // アイコンの設定(現在未使用)
	// ウィンドウ枠の文字設定
	SetMainWindowText("Game");
	// グラフィックモードの設定
	SetGraphMode(width, height, colorBitDepth);
	// ウィンドウモードの設定
	ChangeWindowMode(windowMode);
	//ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	// 描画比率の設定
	SetWindowSizeExtendRate(rate);
	//SetBackgroundColor(0, 0, 0);

	//if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	//{
	//	return -1;			// エラーが起きたら直ちに終了
	//}

	// DXLibの初期化処理
	if (DxLib_Init() == -1) DxLib_End();//エラーが起きたら終了

	//SetDrawScreen(DX_SCREEN_BACK);
	Graphics3D::initialize();
}

void GameDevice::flip()
{
	ScreenFlip();
}
