#ifndef GAMEPLAYTIMER_H_
#define GAMEPLAYTIMER_H_

#include "../../Math/Vector2.h"

class GamePlayTimer {
public:
	// �R���X�g���N�^
	GamePlayTimer();
	// �R���X�g���N�^
	GamePlayTimer(float time, const Vector2 position, int textureNumber);
	// �X�V
	void update(float deltaTime);
	// �^�C���̕`��
	void draw() const;
	// �^�C���̎擾
	int getTime() const;
	// �e�N�X�`���ԍ�
	int textureNumber_;
	// ���Ԑ؂ꂩ�ǂ������擾
	bool getIsTimeOver();

private:
	 float timer_;

	 Vector2 position_;
};

#endif
