#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "../Base/IScene.h"
#include "../../World/World.h"

class TitleScene : public IScene {
public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	virtual ~TitleScene();
	// �J�n
	virtual void start() override;
	// �X�V
	virtual void update(float deltaTime) override;
	// �`��
	virtual void draw() const override;
	// �I�����Ă��邩�H
	virtual bool isEnd() const override;
	// ���̃V�[����Ԃ�
	virtual Scene next() const override;
	// �I��
	virtual void end() override;

private:
	// �{�^���̓����x�^�C�}
	float alphaTimer_;
	// �����摜��X���W
	float kendoPositionX_;
	// ���摜��X���W
	float karatePositionX_;
	// �L�����N�^�[�摜��Y���W
	float characterTexturePositionY_;
	// �摜��X���W���Z���l(�f���^�^�C����������)
	float textureMoveSpeed_;
	// �{�^���̓����x
	float buttonAlpha_;
};

#endif