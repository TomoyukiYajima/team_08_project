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
	// ���s
	int run() {
		// �Q�[���f�o�C�X�̐ݒ�
		GameDevice device(mWidth_, mHeight_, mRate_, mWindowMode_);

		//// �ǂݍ��ރt�H���g�t�@�C���̃p�X
		//LPCSTR font_path = "./resources/file/nikumaru.ttf";
		//if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		//}
		//else {
		//	// �t�H���g�Ǎ��G���[����
		//	MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
		//}
		//ChangeFont("07�ɂ��܂�t�H���g");

		// �J�n����
		start();
		// �L�[���������܂Ń��[�v
		while (isRunning()) {
			update();
			draw();
			// 
			device.flip();
		}
		// �I������
		end();

		/*if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
		}
		else {
			MessageBox(NULL, "remove failure", "", MB_OK);
		}*/

		DxLib_End();	// �c�w���C�u�����g�p�̏I������
		return 0;	// �\�t�g�̏I�� 
	}

private:
	// �J�n����
	virtual void start() {}
	// �X�V����
	virtual void update() {}
	// �`�揈��
	virtual void draw() {}
	// �I������
	virtual void end() {}
	// ���s���� false�Ȃ�I��
	// ScreenFlip()=����ʂ�\��ʂɔ��f����, ProcessMessage()=���b�Z�[�W����, 
	// ClearDrawScreen()=�`��̃N���A
	virtual bool isRunning(){
		return (
			ProcessMessage() == 0 && ClearDrawScreen() == 0 &&
			InputManager::GetInstance().IsKeyDown(KeyCode::ESCAPE) == 0
			);
	}


private:
	// �R�s�[�֎~
	Game(const Game& other) = delete;
	Game& operator = (const Game& other) = delete;

private:
	int mWidth_;			// �E�B���h�E�̉��̑傫��
	int mHeight_;		// �E�B���h�E�̏c�̑傫��
	float mRate_;			// �`��䗦
	int mWindowMode_;	// �t���X�N���[�����H TRUE = 1 �Ńt���X�N���[��
	float mFps_;			// �t���[�����[�g
};

#endif
