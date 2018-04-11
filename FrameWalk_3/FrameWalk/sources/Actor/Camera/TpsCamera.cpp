#include "TpsCamera.h"
#include "../../World/IWorld.h"

TpsCamera::TpsCamera(IWorld* world, Vector3& position) :
	Actor(world, "Camera", Vector3(position.x, position.y + 0.9f, position.z - 4.5f)),
	velocity_(0.0f, 0.0f, 0.0f){}

// �X�V
void TpsCamera::onUpdate(float) 
{
	auto player = world_->findActor("Player");
	if (player == nullptr) return;
	auto position = Vector3(0.0f, 1.0f, -5.0f) * player->getPose();
	//target_ = player->getPosition() + Vector3(0.0f, 1.0f, 0.0f);
	target_ = player->getPosition();
	move(position, 0.5f, 0.1f, 0.8f);
}

// �`��
void TpsCamera::onDraw() const 
{
	auto player = world_->findActor("Player");
	if (player == nullptr) return;

	SetCameraPositionAndTarget_UpVecY(
		player->getPosition() + player->getRotate().Up() * 2 + player->getRotate().Forward() * 3,
		player->getPosition() + player->getRotate().Up()  - player->getRotate().Forward()
		);
}

// �J�����̈ړ�
void TpsCamera::move(
	const Vector3& restPosition,
	float stiffness,
	float friction,
	float mass
	)
{
	// �o�l�̐L�ы���v�Z
	Vector3 stretch = position_ - restPosition;
	// �o�l�̗͂��v�Z
	Vector3 force = -stiffness * stretch;
	// �����x���v�Z
	Vector3 acceleration = force / mass;
	// �ړ��ʂ��v�Z
	velocity_ = friction * (velocity_ + acceleration);
	// ���W�̍X�V
	position_ += velocity_;
}
