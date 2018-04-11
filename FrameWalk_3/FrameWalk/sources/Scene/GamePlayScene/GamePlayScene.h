#ifndef GAMEPLAYSCENE_H_
#define GAMEPLAYSCENE_H_

#include "../Base/IScene.h"
#include "../../World/World.h"
#include "../../Actor/UI/Score.h"
#include "../../Actor/UI/GamePlayTimer.h"
#include "../../Actor/UI/MiniMap.h"
#include "../../Actor/UI/Result.h"

class GamePlayScene : public IScene {
public:
	// �R���X�g���N�^
	GamePlayScene();
	// �f�X�g���N�^
	virtual ~GamePlayScene();
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
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �G�����֐�
	void enemyCreate();
	// ����
	int rankCount();

private:
	using WorldPtr = std::shared_ptr<World>;
	WorldPtr	world_;				// ���[���h
	// �X�R�A
	Score		score_;
	// �Q�[���^�C�}
	GamePlayTimer gameTimer_;
	// ���U���g
	Result result_;
	// �~�j�}�b�v
	MiniMap miniMap_;
	// �G�����J�E���g
	int	enemyCreateCount_;
	bool isGameOver_;
};

#endif