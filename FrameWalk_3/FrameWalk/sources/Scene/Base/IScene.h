#ifndef ISCENE_H_
#define ISCENE_H_

#include "DxLib.h"
#include "Scene.h"
#include "../../Utility/Input/InputManager.h"
#include <string>

class IScene {
public:
	//���z�f�X�g���N�^
	virtual ~IScene() {}
	//������
	virtual void start() = 0;
	//�X�V
	virtual void update(float deltaTime) = 0;
	//�`��
	virtual void draw() const = 0;
	//�I���t���O
	virtual bool isEnd() const = 0;
	//���̃V�[��
	virtual Scene next() const = 0;
	//�I��
	virtual void end() = 0;
	// �V�[�����̎擾
	std::string getName() { return name_; }
	// ���̃V�[�����̎擾
	virtual std::string nextName() { return "next"; }
	// �V�[�����̐ݒ�
	void setName(std::string name) { name_ = name; }

public:
	bool isEnd_;		// �I�����邩�H
	//SceneDataKeeper* keeper_;
	std::string name_;	// �V�[����
};

#endif