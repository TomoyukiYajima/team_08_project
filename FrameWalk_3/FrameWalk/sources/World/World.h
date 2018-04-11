#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>
#include <forward_list>

enum class EventMessage;

class World : public IWorld {
public:
	// �R���X�g���N�^
	World();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �t�B�[���h�̒ǉ�
	void addField(const FieldPtr& field);
	// �J�����̒ǉ�
	void addCamera(const ActorPtr& camera);
	// ���C�g�̒ǉ�
	void addLight(const ActorPtr& light);

	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) override;
	// �A�N�^�[�̌���(forward_list��Ԃ��܂�)
	virtual std::forward_list<ActorPtr>findActors(const ActorGroup group) override;
	// �t�B�[���h���ɑ��݂���A�N�^�[�O���[�v�̐����擾���܂�
	virtual int getActorCount(ActorGroup group) override;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const override;
	// �Q�[���N���A���ǂ�����ݒ肵�܂�
	virtual void setIsGameClear(bool isClear) override;
	// �Q�[���N���A���ǂ�����Ԃ��܂�
	virtual bool isGameClear() override;
	// �����I�ɃQ�[���N���A�����邩��ݒ肵�܂�
	virtual void setIsGameClearEnd(bool isClearEnd) override;
	// �����I�ɃQ�[���N���A���邩��Ԃ��܂�
	virtual bool isGameClearEnd() override;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// �C�x���g���X�i�[�̒ǉ�
	void addEventMessageListener(
		std::function<void(EventMessage, void*)> listener);

	// �R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	// �A�N�^�[�}�l�[�W���[
	ActorManager	actors_;
	// ���C�g
	ActorPtr		light_;
	// �J����
	ActorPtr		camera_;
	// �t�B�[���h
	FieldPtr		field_;
	// �C�x���g���X�i�[
	std::function<void(EventMessage, void*)> listener_;

private:
	bool isClear_;		// �Q�[���N���A���邩
	bool isClearEnd_;	// �Q�[���N���A�ŋ����I�����邩
};

#endif

