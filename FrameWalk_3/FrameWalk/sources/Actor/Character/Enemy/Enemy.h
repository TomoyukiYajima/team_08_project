#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../Base/Actor.h"
#include "../../Base/EventMessage.h"

class IWorld;

// �G
class Enemy : public Actor {
public:
	// ���[�V�����ԍ��N���X
	enum {
		ENEMY_MOTION_IDEL = 9,
		ENEMY_MOTION_WALK = 1,
		ENEMY_MOTION_DAMAGE = 14,
		ENEMY_MOTION_DAMAGE_NOW = 15
	};

public:
	// ��ԃN���X
	enum class State {
		Idel,
		Move,
		LogOut,
		Damage
	};

public:
	Enemy(IWorld* world, const Vector3& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor&) override;
	virtual void onMessage(EventMessage event, void* param) override;

private:
	// ��Ԃ̍X�V
	void updateState(float deltaTime);
	// ��Ԃ̕ύX
	void changeState(State state, const int motion, const bool isLoop = true);
	// �ҋ@
	void idel(float deltaTime, bool isLogOut);
	// �s��
	void move(float deltaTime);
	// �_���[�W��
	void damage(float deltaTime);
	// �G�̓_��
	void flashEnemy(const float minAlpha, const float maxAlpha, float deltaTime);

public:
	// ��Ԃ�Ԃ��܂�
	State getState();

private:
	// �ҋ@����
	float idelTime_;
	// �����ҋ@����
	float initIdelTime_;

private:
	// ���
	State state_;
	// ��ԃ^�C�}
	float stateTimer_;
	int motion_;
	float motionTimer_;

private:
	// �_�ŊԊu
	int flashInterval_;
	// ���A����(���g�p)
	float comebackTime_;
	// �_�Ŏ���
	float flashTime_;
	float alpha_;
};

#endif
