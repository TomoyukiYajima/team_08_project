#include "TpsCamera.h"
#include "../../World/IWorld.h"

TpsCamera::TpsCamera(IWorld* world, Vector3& position) :
	Actor(world, "Camera", Vector3(position.x, position.y + 0.9f, position.z - 4.5f)),
	velocity_(0.0f, 0.0f, 0.0f){}

// 更新
void TpsCamera::onUpdate(float) 
{
	auto player = world_->findActor("Player");
	if (player == nullptr) return;
	auto position = Vector3(0.0f, 1.0f, -5.0f) * player->getPose();
	//target_ = player->getPosition() + Vector3(0.0f, 1.0f, 0.0f);
	target_ = player->getPosition();
	move(position, 0.5f, 0.1f, 0.8f);
}

// 描画
void TpsCamera::onDraw() const 
{
	auto player = world_->findActor("Player");
	if (player == nullptr) return;

	SetCameraPositionAndTarget_UpVecY(
		player->getPosition() + player->getRotate().Up() * 2 + player->getRotate().Forward() * 3,
		player->getPosition() + player->getRotate().Up()  - player->getRotate().Forward()
		);
}

// カメラの移動
void TpsCamera::move(
	const Vector3& restPosition,
	float stiffness,
	float friction,
	float mass
	)
{
	// バネの伸び具合を計算
	Vector3 stretch = position_ - restPosition;
	// バネの力を計算
	Vector3 force = -stiffness * stretch;
	// 加速度を計算
	Vector3 acceleration = force / mass;
	// 移動量を計算
	velocity_ = friction * (velocity_ + acceleration);
	// 座標の更新
	position_ += velocity_;
}
