#ifndef RESULT_H_
#define RESULT_H_

#include "../../Math/Vector2.h"
#include <vector>

class Result {
public:
	// �R���X�g���N�^
	Result();
	// �f�X�g���N�^
	~Result();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �X�R�A���Z�b�g����
	void setScore();
	// �e�̕`��
	void drawShadow(const int textureNumber, const Vector2 position, const int x, const int y, const int w, const int h) const;

private:
	//Vector2 position_;
	// �X�R�A
	int score_;
	// �����N
	int rank_;
	// �V�[���ڍs�^�C�}
	float changeSceneTimer_;
	// �e�N�X�`���̈ړ����x
	float moveSpeed_;
	// �{�^���̓����x
	float buttonAlpha_;
	// ���������摜�̈ʒu
	Vector2 kendoPosition_;
	// �]���R���e�i
	std::vector<float> rankContainer;
	// �X�R�A�R���e�i
	std::vector<int> scoreContainer;
};

#endif