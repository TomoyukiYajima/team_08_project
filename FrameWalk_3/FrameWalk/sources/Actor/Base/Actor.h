#ifndef ACTOR_H_
#define ACTOR_H_

#include "DxLib.h"

#include "ActorPtr.h"
#include "ActorGroup.h"
#include "../../Math/Math.h"
#include "../../Math/Collision/BoundingSphere.h"
#include <string>
#include <memory>
#include <functional>
#include <forward_list>

class IWorld;

enum class EventMessage;

class Actor {
public:
	// �R���X�g���N�^
	//Actor(IWorld* world, const std::string& name, const GSvector3& position, const BoundingSphere& body);
	Actor(
		IWorld* world, const std::string& name, 
		const Vector3& position, const BoundingSphere& body = BoundingSphere(0.0f)
		);
	// �R���X�g���N�^
	explicit Actor(const std::string& name = "none");
	// ���z�f�X�g���N�^
	virtual ~Actor() {}
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �Փˏ���
	void collide(Actor& other);
	// �n�`�Ƃ̏Փˏ������s���܂�
	void collideField(int FieldHandle, float deltaTime);
	// 
	void setIsHit(bool isHit);
	// ���S���Ă��邩�H
	bool isDead() const;
	// ���S����
	void dead();
	// ���O��Ԃ�
	const std::string& getName() const;
	// ���W��Ԃ�
	Vector3 getPosition() const;
	// ��]�s���Ԃ�
	Matrix getRotate() const;
	// �ϊ��s���Ԃ�
	Matrix getPose() const;
	// 
	BoundingSphere getBody() const;
	// �ʒu��ݒ肵�܂�
	void setPosition(const Vector3& position);
	// 
	void setPose(const Matrix& rotate);
	// �A�N�^�[�O���[�v���擾���܂�
	void setActorGroup(ActorGroup group);
	// �A�N�^�[�O���[�v��Ԃ��܂�
	ActorGroup getActorGroup();
	// �t�B�[���h���ɑ��݂���A�N�^�[�O���[�v�̐����擾���܂�
	int getActorCount();
	// �U���͂��擾���܂�
	int getAP() const;

public:
	// �q�̌���
	ActorPtr findCildren(const std::string& name);
	// �q�̌���
	ActorPtr findCildren(std::function<bool (const Actor&)> fn);
	// �q���擾
	std::forward_list<ActorPtr> getChildren();
	// �q���m�̏Փ�
	void collideChildren(Actor& other);
	// �Z�퓯�m�̏Փ˔���
	void collideSibling();
	// �q�̒ǉ�
	void addChild(const ActorPtr& child);
	// �q������
	void eachChildren(std::function<void(Actor&)> fn);
	// �q������(const��)
	void eachChildren(std::function<void(const Actor&)> fn) const;
	// �q���폜����
	void removeChildren(std::function <bool(Actor&)> fn);
	// �q���폜����
	void removeChildren();
	// �q������
	void clearChildren();
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);
	// �Փ˔���
	bool isCollide(const Actor& other) const;

protected:
	// ���[���h
	IWorld*	world_;
	// ���O
	std::string	name_;
	// ���W
	Vector3	position_;
	// ��]
	Matrix rotate_;
	// �Փ˔���
	BoundingSphere body_;
	// �A�N�^�[�O���[�v
	ActorGroup actorGroup_;
	// ���S�t���O
	bool dead_;
	// �����蔻������邩
	bool isCollideHit_;
	// �d�͂��g����
	bool isUseGravity_;
	// �̗�
	int hp_;
	int initHp_;
	// �U����
	int ap_;
	int initAp_;

private:
	float fallTime_;	// ��������
	// �q�A�N�^�[
	std::forward_list<ActorPtr> children_;
};

#endif
