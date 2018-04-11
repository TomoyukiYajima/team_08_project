#include "Bullet.h"

Bullet::Bullet(IWorld * world, const Vector3 & position) :
	Actor(world, "Bullet", position, BoundingSphere(1.0f)),
	deleteTime_(0.0f)
{
	deleteTime_ = 30.0f;
}

void Bullet::onUpdate(float deltaTime)
{
	deleteTime_ -= deltaTime;

	if (deleteTime_ <= 0.0f) dead();
}

void Bullet::onCollide(Actor &) {}

//void Bullet::onDraw() const
//{
//	body_.draw(position_);
//}
