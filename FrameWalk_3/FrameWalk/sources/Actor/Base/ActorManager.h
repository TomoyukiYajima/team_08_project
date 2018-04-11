#ifndef ACTOR_MANAGER_H_
#define ACTOR_MANAGER_H_

#include "Actor.h"
#include <unordered_map>

enum class ActorGroup;

class ActorManager {
public:
	// �R���X�g���N�^
	ActorManager();
	// ������
	void initialize();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �A�N�^�[�̒ǉ�
	void addActor(ActorGroup group, const ActorPtr& actor);
	// �A�N�^�[�̌���
	ActorPtr findActor(const std::string& name);
	// �t�B�[���h���ɑ��݂���A�N�^�[�O���[�v�̐����擾���܂�
	int getActorCount(ActorGroup group);
	//�A�N�^�[���O���[�v�Ŏ擾���܂�
	std::forward_list<ActorPtr> GetActors(const ActorGroup group);
	// �A�N�^�[�̃O���[�v��ύX���܂�
	void changeActorGroup(ActorGroup group, const ActorPtr& actor);
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	// �Փ˔���
	void collide();

private:
	// ���[�g�m�[�h
	Actor root_;
	// �A�N�^�[�O���[�v
	std::unordered_map<ActorGroup, ActorPtr> actors_;
};

#endif