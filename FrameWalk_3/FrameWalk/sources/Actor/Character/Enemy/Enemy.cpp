#include "Enemy.h"
#include "../../../World/IWorld.h"
#include "../../../Field/Field.h"
#include "../../../Utility/Resource/Mesh/SkeletalMesh.h"
#include "../../../Utility/Resource/Sound/Sound.h"

Enemy::Enemy(IWorld * world, const Vector3 & position) :
	Actor(world, "Enemy", position, BoundingSphere(position, 0.0f)),
	idelTime_(0.0f),
	initIdelTime_(0.0f),
	motion_(ENEMY_MOTION_IDEL),
	motionTimer_(0.0f),
	state_(State::Idel),
	flashInterval_(0),
	stateTimer_(0.0f),
	flashTime_(0.0f),
	alpha_(1.0f){
	idelTime_ = 1.0f * 60.0f;
	initIdelTime_ = idelTime_;
	flashInterval_ = 10;

	// 生成カウントに加算する
	static const int count = -1;
	world_->sendMessage(EventMessage::AddEnemyCount, (void*)&count);

	// プレイヤーを探す
	auto player = world_->findActor("Player");
	if (player == nullptr) return;
	// 追尾時に一回だけ向くようにする
	auto target = (player->getPosition() - position_).Normalize();
	// 相手の方向を向くベクトルの計算
	Matrix target_rotate =
		Matrix::CreateWorld(Vector3::Zero, -target, rotate_.Up());
	rotate_ = target_rotate;
}

void Enemy::onUpdate(float deltaTime) {
	// 状態の更新
	updateState(deltaTime);
	// アニメーションの更新
	SkeletalMesh::bind((int)ModelID::ENEMY_MODEL);
	motionTimer_ = std::fmod(motionTimer_ + 0.5f * deltaTime, SkeletalMesh::end_time(motion_));
}

void Enemy::onDraw() const {
	SkeletalMesh::bind((int)ModelID::ENEMY_MODEL);
	SkeletalMesh::bind_animation(motion_, motionTimer_);
	SkeletalMesh::transform(Matrix(rotate_).Translation(position_));
	SkeletalMesh::draw(alpha_);
}

void Enemy::onCollide(Actor& other) {
	// ダメージ処理ならすぐに返す
	if (state_ == State::Damage || state_ == State::Idel) return;
	changeState(State::Damage, ENEMY_MOTION_DAMAGE);
	body_.radius = 0.0f;
	// スコア加算
	if (other.getActorGroup() != ActorGroup::PlayerBullet) return;
	Sound::play_se((int)SoundID::SE_ATTACK2);
	static const int score = 1;
	world_->sendMessage(EventMessage::AddScore, (void*)&score);
}

void Enemy::onMessage(EventMessage event, void *) {
	switch (event) {
	case EventMessage::EnemyDead:
		dead();
		break;
	}
}

// 状態の更新
void Enemy::updateState(float deltaTime) {
	switch (state_)
	{
	case State::Idel: idel(deltaTime, false); break;
	case State::Move: move(deltaTime); break;
	case State::Damage: damage(deltaTime); break;
	case State::LogOut: idel(deltaTime, true); break;
	};

	stateTimer_ += deltaTime;
	// 地形との判定
	collideField(world_->getField()->getFieldHendle(), deltaTime);
}

// 状態の変更
void Enemy::changeState(State state, const int motion, const bool isLoop)
{
	if (state_ == state) return;
	motion_ = motion;
	motionTimer_ = 0.0f;
	state_ = state;
	stateTimer_ = 0.0f;
}

// 待機
void Enemy::idel(float deltaTime, bool isLogOut) {
	idelTime_ -= deltaTime;
	flashEnemy(0.0f, 1.0f, deltaTime);
	// 一定時間経過したら移動行動に変更する
	if (idelTime_ <= 0.0f) {
		if (isLogOut) {
			dead();
			// 生成カウントに加算する
			static const int count = 1;
			world_->sendMessage(EventMessage::AddEnemyCount, (void*)&count);
			return;
		}
		changeState(State::Move, ENEMY_MOTION_WALK);
		// 待機時間の初期化
		idelTime_ = initIdelTime_;
		body_.radius = 0.5f;
		alpha_ = 1.0f;;
		return;
	}
}

// 状態の更新
void Enemy::move(float deltaTime) {
	float front_speed = -0.1f;
	position_ += rotate_.Forward() * front_speed * deltaTime;
	// 画面外であれば死亡
	if (world_->getField()->isOutside(position_, Vector3(1.2f, 0.0f, 1.2f))) {
		changeState(State::LogOut, ENEMY_MOTION_IDEL);
		body_.radius = 0.0f;
		return;
	}
}

// ダメージ中
void Enemy::damage(float deltaTime) {
	// 動作が終わるまでダメージ
	//body_.radius = 0.0f;
	flashEnemy(0.0f, 1.0f, deltaTime);
	if (stateTimer_ < SkeletalMesh::end_time(motion_)) return;
	//mesh_.changeMotion(ENEMY_MOTION_DAMAGE_NOW);
	// 生成カウントに加算する
	static const int count = 1;
	world_->sendMessage(EventMessage::AddEnemyCount, (void*)&count);
	dead();
}

// 敵の点滅
void Enemy::flashEnemy(const float minAlpha, const float maxAlpha, float deltaTime) {
	// カウントの余りが 
	flashTime_ += deltaTime;
	if ((int)flashTime_ % flashInterval_ > flashInterval_ / 2) alpha_ = minAlpha;
	else alpha_ =  maxAlpha;
}

Enemy::State Enemy::getState()
{
	return state_;
}
