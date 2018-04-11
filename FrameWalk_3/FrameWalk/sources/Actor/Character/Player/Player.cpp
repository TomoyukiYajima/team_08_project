#include "Player.h"
#include "Bullet.h"
#include "../../../World/IWorld.h"
#include "../../../Field/Field.h"
#include "../../../Utility/Input/InputManager.h"
#include "../../../Utility/Resource/Mesh/SkeletalMesh.h"
#include "../../../Utility/Resource/Sound/Sound.h"

Player::Player(IWorld * world, const Vector3 & position) :
	Actor(world, "Player", position, BoundingSphere(position, 0.5f)),
	//mesh_(MV1LoadModel("./resources/model/Kendo/Kendo.mv1"), MOTION_IDEL, true),
	state_(State::Move),
	stateTimer_(0.0f),
	motion_(MOTION_IDEL),
	motionTimer_(0.0f)
{
}

void Player::onUpdate(float deltaTime)
{
	// 状態の更新
	updateState(deltaTime);
	// アニメーションの更新
	SkeletalMesh::bind((int)ModelID::PLAYER_MODEL);
	motionTimer_ = std::fmod(motionTimer_ + 0.5f * deltaTime, SkeletalMesh::end_time(motion_));
	// ステージの大きさにクランプする
	position_.x = MathHelper::Clamp(
		position_.x,
		-world_->getField()->getFieldScale().x,
		world_->getField()->getFieldScale().x);
	position_.z = MathHelper::Clamp(
		position_.z,
		-world_->getField()->getFieldScale().z,
		world_->getField()->getFieldScale().z);
}

void Player::onDraw() const
{
	// アニメーションの描画
	SkeletalMesh::bind((int)ModelID::PLAYER_MODEL);
	SkeletalMesh::bind_animation(motion_, motionTimer_);
	SkeletalMesh::transform(Matrix(rotate_).Translation(position_));
	SkeletalMesh::draw();
}

void Player::onCollide(Actor &)
{
	if (state_ == State::Damage || state_ == State::ComeBack) return;
	changeState(State::Damage, MOTION_DAMAGE);
	Sound::play_se((int)SoundID::SE_DAMAGE);
	return;
}

void Player::onMessage(EventMessage event, void * param)
{
}

void Player::updateState(float deltaTime)
{
	switch (state_)
	{
	case State::Move: move(deltaTime); break;
	case State::Attack: attack(deltaTime); break;
	case State::Damage: damage(deltaTime); break;
	case State::ComeBack: comeback(deltaTime); break;
	};
	stateTimer_ += deltaTime;

	// 地形との判定
	collideField(world_->getField()->getFieldHendle(), deltaTime);
}

void Player::changeState(State state, const int motion, const bool isLoop)
{
	if (state_ == state) return;
	motion_ = motion;
	motionTimer_ = 0.0f;
	state_ = state;
	stateTimer_ = 0.0f;
}

void Player::move(float deltaTime)
{
	// 攻撃
	if (InputManager::GetInstance().IsKeyDown(KeyCode::SPACE)) {
		changeState(State::Attack, MOTION_ATTACK, false);
		world_->addActor(
			ActorGroup::PlayerBullet,
			std::make_shared<Bullet>(world_,position_ + rotate_.Forward() * -2 + rotate_.Up())
			);
		Sound::play_se((int)SoundID::SE_ATTACK1);
		return;
	}

	auto motion = MOTION_IDEL;
	auto angle = 0.0f;
	// 移動
	auto forward_speed = 0.0f;
	if (InputManager::GetInstance().IsKeyOn(KeyCode::RIGHT)) {
		angle = 2.0f;
	}
	else if (InputManager::GetInstance().IsKeyOn(KeyCode::LEFT)) {
		angle = -2.0f;
	}
	if (InputManager::GetInstance().IsKeyOn(KeyCode::UP)) {
		forward_speed = -0.1f;
	}
	//else if (InputManager::GetInstance().IsKeyOn(KeyCode::DOWN)) {
	//	forward_speed = 0.25;
	//}

	position_ += rotate_.Forward() * forward_speed * deltaTime;
	if (forward_speed != 0.0f) {
		motion = MOTION_WALK;
	}

	rotate_ *= Matrix::CreateFromAxisAngle(rotate_.Up(), angle * deltaTime);
	rotate_.NormalizeRotationMatrix();

	motion_ = motion;
}

void Player::attack(float deltaTime)
{
	if (stateTimer_ < SkeletalMesh::end_time(motion_)) return;
	changeState(State::Move, MOTION_IDEL);
}

void Player::damage(float deltaTime)
{
	if (stateTimer_ < SkeletalMesh::end_time(motion_)) return;
	changeState(State::ComeBack, MOTION_COMEBACK, false);
}

void Player::comeback(float deltaTime)
{
	if (stateTimer_ < SkeletalMesh::end_time(motion_) - 6.0f) return;
	changeState(State::Move, MOTION_IDEL);
}
