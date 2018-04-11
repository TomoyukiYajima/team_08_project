#ifndef IWORLD_H_
#define IWORLD_H_

#include "../Actor/Base/ActorPtr.h"
#include "../Field/FieldPtr.h"
#include <string>
#include <forward_list>

enum class ActorGroup;
enum class EventMessage;

// ���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	// ���z�f�X�g���N�^
	virtual ~IWorld() {}
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) = 0;
	// �A�N�^�[�̌���(forward_list��Ԃ��܂�)
	virtual std::forward_list<ActorPtr>findActors(const ActorGroup group) = 0;
	// �t�B�[���h���ɑ��݂���A�N�^�[�O���[�v�̐����擾���܂�
	virtual int getActorCount(ActorGroup group) = 0;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const = 0;
	// �Q�[���N���A���ǂ�����ݒ肵�܂�
	virtual void setIsGameClear(bool isClear) = 0;
	// �Q�[���N���A���ǂ�����Ԃ��܂�
	virtual bool isGameClear() = 0;
	// �����I�ɃQ�[���N���A�����邩��ݒ肵�܂�
	virtual void setIsGameClearEnd(bool isClearEnd) = 0;
	// �����I�ɃQ�[���N���A���邩��Ԃ��܂�
	virtual bool isGameClearEnd() = 0;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
};

#endif
