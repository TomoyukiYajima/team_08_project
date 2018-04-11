#ifndef TPS_CAMERA_H_
#define TPS_CAMERA_H_

#include "../Base/Actor.h"

class TpsCamera : public Actor {
public:
	// �R���X�g���N�^
	explicit TpsCamera(IWorld* world, Vector3& position);
private:
	// �X�V
	virtual void onUpdate(float deltaTime) override;
	// �`��
	virtual void onDraw() const override;
	// �J�����̈ړ�
	void move(
		const Vector3& restPosition,
		float stiffness,
		float friction,
		float mass
	);

private:
	// �ړ���
	Vector3 velocity_;
	// �ڕW�ʒu
	Vector3 target_;
};

#endif
