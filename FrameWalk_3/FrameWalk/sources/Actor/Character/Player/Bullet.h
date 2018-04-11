#ifndef BULLET_H_
#define BULLET_H_

#include "../../Base/Actor.h"

// �e�N���X
class Bullet : public Actor {
public:
	// �R���X�g���N�^
	Bullet(IWorld* world, const Vector3& position);
	// �X�V
	virtual void onUpdate(float deltaTime) override;
	virtual void onCollide(Actor&) override;
	//virtual void onDraw() const override;

private:
	// �����^�C��
	float deleteTime_;
	// �ړ���
	//Vector3 velocity_;
};

#endif

