#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Base/Actor.h"

class IWorld;

class Player : public Actor {
private:
	// ��ԃN���X
	enum class State {
		Idel,
		Move,
		Attack,
		Damage,
		ComeBack,
		Dead,
		ResPorn,
	};
	// ���[�V�����ԍ�
	enum {
		MOTION_IDEL = 0,
		MOTION_WALK = 1,
		MOTION_ATTACK = 17,
		MOTION_DAMAGE = 14,
		MOTION_DAMAGENOW = 15,
		MOTION_COMEBACK = 16,
		MOTION_DEAD = 20,
		MOTION_RESPORN = 21
	};

public:
	Player(IWorld* world, const Vector3& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor&) override;
	virtual void onMessage(EventMessage event, void* param) override;

// ��Ԋ֘A
private:
	// ��Ԃ̍X�V
	void updateState(float deltaTime);
	// ��Ԃ̕ύX
	void changeState(State state, const int motion, const bool isLoop = true);
	// ��Ԃ̍X�V
	void move(float deltaTime);
	// �U����
	void attack(float deltaTime);
	// �_���[�W��
	void damage(float deltaTime);
	// ���A��
	void comeback(float deltaTime);

private:
	State state_;				// ���
	float stateTimer_;			// ��ԃ^�C�}
	int motion_;
	float motionTimer_;
};

#endif