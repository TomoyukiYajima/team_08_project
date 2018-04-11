#include "Actor.h"
#include "../../Define.h"
#include <algorithm>

// �R���X�g���N�^
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

// �R���X�g���N�^
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(0.0f, 0.0f, 0.0f),
	rotate_(Matrix::Identity),
	dead_(false),
	ap_(0) {
}


// �X�V
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	body_.center = position_;
	eachChildren([&](Actor& child) { child.update(deltaTime); });
}

// �`��
void Actor::draw() const {
	onDraw();
	eachChildren([&](const Actor& child) { child.draw(); });
}


// �Փ˔���
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
	// ���f���̃R���W�������̎擾
	MV1SetupCollInfo(FieldHandle);
	// ���f���Ɛ����̔���
	auto hit = MV1CollCheck_Line(
		FieldHandle, -1,
		position_ + Vector3::Up * 10.0f,
		position_ + Vector3::Down * 1000.0f);
	// �Փ˂����ꍇ�͕␳����
	if (hit.HitFlag == 1) {
		auto hitPos = hit.HitPosition;
		// �ڒn���Ă��Ȃ������痎����
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

//// �Փ˔���(�I�N�c���[�̃I�u�W�F�N�g)
//void Actor::octreeCollide(const GSuint OctreeNumber) {
//	if (!isOctreeCollide(OctreeNumber)) return;
//
//}

// 
void Actor::setIsHit(bool isHit) { isCollideHit_ = isHit; }

// ���S���Ă��邩�H
bool Actor::isDead() const { return dead_; }

// ���S����
void Actor::dead() { dead_ = true; }

// ���O��Ԃ�
const std::string & Actor::getName() const { return name_; }

// ���W��Ԃ�
Vector3 Actor::getPosition() const { return position_; }

// ��]�s���Ԃ�
Matrix Actor::getRotate() const { return rotate_; }

// �ϊ��s���Ԃ�
Matrix Actor::getPose() const {
	return Matrix().Translation(position_);
}

BoundingSphere Actor::getBody() const
{
	return body_.transform(getPose());
}

// �ʒu��ݒ肵�܂�
void Actor::setPosition(const Vector3 & position) { position_ = position; }

void Actor::setPose(const Matrix & rotate) { rotate_ = const_cast<Matrix&>(rotate); }

// �A�N�^�[�O���[�v��ݒ肵�܂�
void Actor::setActorGroup(ActorGroup group) { 
	
	actorGroup_ = group;
}

// �A�N�^�[�O���[�v��Ԃ��܂�
ActorGroup Actor::getActorGroup() { return actorGroup_; }

// �t�B�[���h���ɑ��݂���A�N�^�[�O���[�v�̐����擾���܂�
int Actor::getActorCount()
{
	return std::distance(children_.begin(), children_.end());
}

// �U���͂��擾���܂�
int Actor::getAP() const { return ap_; }

// �q�̌���
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// �q�̌���
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

// �q���擾
std::forward_list<ActorPtr> Actor::getChildren()
{
	return children_;
}

// �q�̏Փ˔���
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
			other.eachChildren([&](Actor& target) { my.collide(target); });
		});
}

// �q�̏Փ˔���
void Actor::collideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->collide(*actor); });
	}
}

// �q�̒ǉ�
void Actor::addChild(const ActorPtr& child) { children_.push_front(child); }

// �q������
void Actor::eachChildren(std::function<void (Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q������ (const�Łj
void Actor::eachChildren(std::function<void (const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q���폜
void Actor::removeChildren() {
	// ���S���Ă��邩�𒲂ׂ�
	removeChildren([](Actor& child) { return child.isDead(); });
	//�q�����񂳂���֐��ŉ񂵂Ċm���߂�
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// �q���폜
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	// true�Ȃ�폜����
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

// �q������
void Actor::clearChildren() { children_.clear(); }

// ���b�Z�[�W����
void Actor::handleMessage(EventMessage message, void* param) {
	onMessage(message, param);
	eachChildren([&](Actor& child) { child.handleMessage(message, param); });
}

// ���b�Z�[�W����
void Actor::onMessage(EventMessage, void*) {}

// �X�V
void Actor::onUpdate(float) {}

// �`��
void Actor::onDraw() const {
	//body_.translate(position_).draw(); // �f�o�b�O�\��
}

// �Փ˂���
void Actor::onCollide(Actor&) { dead(); }

// �Փ˔���
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