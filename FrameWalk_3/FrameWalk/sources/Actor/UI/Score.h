#ifndef SCORE_H_
#define SCORE_H_

#include "../../Math/Vector2.h"

// �X�R�A�N���X
class Score {
public:
	// �R���X�g���N�^
	explicit Score(int score = 0);
	// �R���X�g���N�^
	Score(int score, const Vector2& position, const int textureNumber);
	// �X�R�A�̉��Z
	void add(int score);
	// �X�R�A�̕`��
	void draw() const;
	// �X�R�A�̎擾
	int get() const;

private:
	// �X�R�A
	int score_;
	// �e�N�X�`���ԍ�
	int textureNumber_;
	// �ʒu
	Vector2 position_;
};

#endif

