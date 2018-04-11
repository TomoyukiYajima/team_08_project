#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Game.h"
#include "../Scene/Base/SceneManager.h"

class GameManager : public Game {
public:
	GameManager();
	~GameManager(){}
private:
	// �J�n
	virtual void start() override;
	// �X�V
	virtual void update() override;
	// �`��
	virtual void draw() override;
	// �I��
	virtual void end() override;

private:
	// �V�[���}�l�[�W���[
	SceneManager sceneManager_;
};

#endif
