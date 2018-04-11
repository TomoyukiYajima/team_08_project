#include "Actor.h"
#include "../../Define.h"
#include <algorithm>

// コンストラクタ
Actor::Actor(
	IWorld * world, const std::string & name, 
	const Vector3 & position, const BoundingSphere & body) :
	world_(world),
	name_(name),
	position_(position),
	rotate_(Matrix::Identity),
	body_(body),
	actorGroup_(ActorGroup::NULL_GROUP),
	dead_(false),
	isUseGravity_(true),
	isCollideHit_(true),
	hp_(1),
	initHp_(hp_),
	ap_(0),
	initAp_(ap_),
	fallTime_(0.0f){
}

// コンストラクタ
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(0.0f, 0.0f, 0.0f),
	rotate_(Matrix::Identity),
	dead_(false),
	ap_(0) {
}


// 更新
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	body_.center = position_;
	eachChildren([&](Actor& child) { child.update(deltaTime); });
}

// 描画
void Actor::draw() const {
	onDraw();
	eachChildren([&](const Actor& child) { child.draw(); });
}


// 衝突判定
void Actor::collide(Actor& other) {
	if (!isCollideHit_) return;
	if (isCollide(other)) {
		onCollide(other);
		other.onCollide(*this);
	}
	eachChildren([&](Actor& child) { child.collide(other); });
}

void Actor::collideField(int FieldHandle, float deltaTime)
{
	// モデルのコリジョン情報の取得
	MV1SetupCollInfo(FieldHandle);
	// モデルと線分の判定
	auto hit = MV1CollCheck_Line(
		FieldHandle, -1,
		position_ + Vector3::Up * 10.0f,
		position_ + Vector3::Down * 1000.0f);
	// 衝突した場合は補正する
	if (hit.HitFlag == 1) {
		auto hitPos = hit.HitPosition;
		// 接地していなかったら落ちる
		if (isUseGravity_) {
			if (position_.y > hitPos.y) {
				fallTime_ += deltaTime;
				position_.y -= GRAVITY * fallTime_;
			}
			else fallTime_ = 0.0f;
		}
		position_.y = max(position_.y, hitPos.y);
	}
}

//// 衝突判定(オクツリーのオブジェクト)
//void Actor::octreeCollide(const GSuint OctreeNumber) {
//	if (!isOctreeCollide(OctreeNumber)) return;
//
//}

// 
void Actor::setIsHit(bool isHit) { isCollideHit_ = isHit; }

// 死亡しているか？
bool Actor::isDead() const { return dead_; }

// 死亡する
void Actor::dead() { dead_ = true; }

// 名前を返す
const std::string & Actor::getName() const { return name_; }

// 座標を返す
Vector3 Actor::getPosition() const { return position_; }

// 回転行列を返す
Matrix Actor::getRotate() const { return rotate_; }

// 変換行列を返す
Matrix Actor::getPose() const {
	return Matrix().Translation(position_);
}

BoundingSphere Actor::getBody() const
{
	return body_.transform(getPose());
}

// 位置を設定します
void Actor::setPosition(const Vector3 & position) { position_ = position; }

void Actor::setPose(const Matrix & rotate) { rotate_ = const_cast<Matrix&>(rotate); }

// アクターグループを設定します
void Actor::setActorGroup(ActorGroup group) { 
	
	actorGroup_ = group;
}

// アクターグループを返します
ActorGroup Actor::getActorGroup() { return actorGroup_; }

// フィールド内に存在するアクターグループの数を取得します
int Actor::getActorCount()
{
	return std::distance(children_.begin(), children_.end());
}

// 攻撃力を取得します
int Actor::getAP() const { return ap_; }

// 子の検索
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// 子の検索
ActorPtr Actor::findCildren(std::function<bool (const Actor&)> fn) {
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	return nullptr;
}

// 子を取得
std::forward_list<ActorPtr> Actor::getChildren()
{
	return children_;
}

// 子の衝突判定
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
			other.eachChildren([&](Actor& target) { my.collide(target); });
		});
}

// 子の衝突判定
void Actor::collideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->collide(*actor); });
	}
}

// 子の追加
void Actor::addChild(const ActorPtr& child) { children_.push_front(child); }

// 子を巡回
void Actor::eachChildren(std::function<void (Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// 子を巡回 (const版）
void Actor::eachChildren(std::function<void (const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// 子を削除
void Actor::removeChildren() {
	// 死亡しているかを調べる
	removeChildren([](Actor& child) { return child.isDead(); });
	//子を巡回させる関数で回して確かめる
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// 子を削除
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	// trueなら削除する
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

// 子を消去
void Actor::clearChildren() { children_.clear(); }

// メッセージ処理
void Actor::handleMessage(EventMessage message, void* param) {
	onMessage(message, param);
	eachChildren([&](Actor& child) { child.handleMessage(message, param); });
}

// メッセージ処理
void Actor::onMessage(EventMessage, void*) {}

// 更新
void Actor::onUpdate(float) {}

// 描画
void Actor::onDraw() const {
	//body_.translate(position_).draw(); // デバッグ表示
}

// 衝突した
void Actor::onCollide(Actor&) { dead(); }

// 衝突判定
bool Actor::isCollide(const Actor& other) const {
	if (body_.radius == 0.0f) return false;

	return other.getBody().intersects(body_);
	//return getBody().intersects(other.getBody());

	/*return
		(other.position_.x - position_.x) * (other.position_.x - position_.x) +
		(other.position_.y - position_.y) * (other.position_.y - position_.y) +
		(other.position_.z - position_.z) * (other.position_.z - position_.z) <
		(body_.radius + other.body_.radius) * (body_.radius + other.body_.radius);*/
}