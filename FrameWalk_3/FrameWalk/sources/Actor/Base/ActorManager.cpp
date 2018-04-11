#include "ActorManager.h"
#include "ActorGroup.h"

// �R���X�g���N�^
ActorManager::ActorManager() {
	initialize();
}

// ������
void ActorManager::initialize() {
	actors_[ActorGroup::BuilDing] = std::make_shared<Actor>();
	actors_[ActorGroup::GimmickObject] = std::make_shared<Actor>();
	actors_[ActorGroup::Player] = std::make_shared<Actor>();
	actors_[ActorGroup::PlayerBullet] = std::make_shared<Actor>();
	actors_[ActorGroup::Enemy] = std::make_shared<Actor>();
	actors_[ActorGroup::EnemyBullet] = std::make_shared<Actor>();
	actors_[ActorGroup::Effect] = std::make_shared<Actor>();
	root_.clearChildren();
	// �`�揇�ɒǉ�
	root_.addChild(actors_[ActorGroup::Effect]);
	root_.addChild(actors_[ActorGroup::Player]);
	root_.addChild(actors_[ActorGroup::EnemyBullet]);
	root_.addChild(actors_[ActorGroup::PlayerBullet]);
	root_.addChild(actors_[ActorGroup::Enemy]);
	root_.addChild(actors_[ActorGroup::GimmickObject]);
	root_.addChild(actors_[ActorGroup::BuilDing]);
}

// �X�V
void ActorManager::update(float deltaTime) {
	root_.update(deltaTime);
	collide();
	root_.removeChildren();
}

// �`��
void ActorManager::draw() const {
	root_.draw();
}

// �A�N�^�[�̒ǉ�
void ActorManager::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_[group]->addChild(actor);
	actor->setActorGroup(group);
}

// �A�N�^�[�̌���
ActorPtr ActorManager::findActor(const std::string& name) {
	return root_.findCildren(name);
}

// �t�B�[���h���ɑ��݂���A�N�^�[�O���[�v�̐����擾���܂�
int ActorManager::getActorCount(ActorGroup group)
{
	return actors_[group]->getActorCount();
}

//�A�N�^�[���O���[�v�Ŏ擾���܂�
std::forward_list<ActorPtr> ActorManager::GetActors(const ActorGroup group)
{
	return actors_[group]->getChildren();
}

// �A�N�^�[�̃O���[�v��ύX���܂�
void ActorManager::changeActorGroup(ActorGroup group, const ActorPtr & actor)
{
	// �ǉ�
	actors_[group]->addChild(actor);
	// 
	auto actors = GetActors(group);
	for (auto i = actors.begin(); i != actors.end(); ++i) {
		auto ac = *i;
		if (ac != actor) continue;
		// ����̃A�N�^�[
		//actors_[ac->getActorGroup()]->removeChildren();
		actor->setActorGroup(group);
		break;
	}
}

// ���b�Z�[�W����
void ActorManager::handleMessage(EventMessage message, void* param) {
	root_.handleMessage(message, param);
}

// �Փ˔���
void ActorManager::collide() {
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy]);
	//actors_[ActorGroup::Enemy]->collideChildren(*actors_[ActorGroup::Player]);
	//actors_[ActorGroup::Enemy]->collideChildren(*actors_[ActorGroup::Enemy]);
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::EnemyBullet]);
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::BuilDing]);
	actors_[ActorGroup::PlayerBullet]->collideChildren(*actors_[ActorGroup::Enemy]);
}
