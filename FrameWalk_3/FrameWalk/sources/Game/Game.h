#ifndef GAME_H_
#define GAME_H_

#include "DxLib.h"
#include "GameDevice.h"
#include "../Utility/Input/InputManager.h"

class Game {
protected:
	Game(const char* windowName = "GameSample",
		int width = 800, int height = 600,
		float rate = 1.0f, int windowMode = TRUE,
		float fps = 60.0f) :
		mWidth_(width), mHeight_(height), mRate_(rate), mWindowMode_(windowMode),
		mFps_(fps){}

public:
	// 実行
	int run() {
		// ゲームデバイスの設定
		GameDevice device(mWidth_, mHeight_, mRate_, mWindowMode_);

		//// 読み込むフォントファイルのパス
		//LPCSTR font_path = "./resources/file/nikumaru.ttf";
		//if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		//}
		//else {
		//	// フォント読込エラー処理
		//	MessageBox(NULL, "フォント読込失敗", "", MB_OK);
		//}
		//ChangeFont("07にくまるフォント");

		// 開始処理
		start();
		// キーが押されるまでループ
		while (isRunning()) {
			update();
			draw();
			// 
			device.flip();
		}
		// 終了処理
		end();

		/*if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
		}
		else {
			MessageBox(NULL, "remove failure", "", MB_OK);
		}*/

		DxLib_End();	// ＤＸライブラリ使用の終了処理
		return 0;	// ソフトの終了 
	}

private:
	// 開始処理
	virtual void start() {}
	// 更新処理
	virtual void update() {}
	// 描画処理
	virtual void draw() {}
	// 終了処理
	virtual void end() {}
	// 実行中か falseなら終了
	// ScreenFlip()=裏画面を表画面に反映する, ProcessMessage()=メッセージ処理, 
	// ClearDrawScreen()=描画のクリア
	virtual bool isRunning(){
		return (
			ProcessMessage() == 0 && ClearDrawScreen() == 0 &&
			InputManager::GetInstance().IsKeyDown(KeyCode::ESCAPE) == 0
			);
	}


private:
	// コピー禁止
	Game(const Game& other) = delete;
	Game& operator = (const Game& other) = delete;

private:
	int mWidth_;			// ウィンドウの横の大きさ
	int mHeight_;		// ウィンドウの縦の大きさ
	float mRate_;			// 描画比率
	int mWindowMode_;	// フルスクリーンか？ TRUE = 1 でフルスクリーン
	float mFps_;			// フレームレート
};

#endif
