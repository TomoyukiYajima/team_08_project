#include "World.h"
#include "../Field/Field.h"

// �R���X�g���N�^
World::World() :
	listener_([](EventMessage, void*) {}),
	isClear_(false),
	isClearEnd_(false){
}

// �X�V
void World::update(float deltaTime) {
	actors_.update(deltaTime);
	camera_->update(deltaTime);
	//light_->update(deltaTime);
}

// �`��
void World::draw() const {
	camera_->draw();
	//light_->draw();
	field_->draw();
	actors_.draw();
}

// ���b�Z�[�W����
void World::handleMessage(EventMessage message, void* param) {
	// ���[���h�̃��b�Z�[�W����
	listener_(message, param);
	// �A�N�^�[�̃��b�Z�[�W����
	actors_.handleMessage(message, param);
	camera_->handleMessage(message, param);
	//light_->handleMessage(message, param);
}
 
// �t�B�[���h�̒ǉ�
void World::addField(const FieldPtr& field) {
	field_ = field;
}

// �J�����̒ǉ�
void World::addCamera(const ActorPtr& camera) {
	camera_ = camera;
}

// ���C�g�̒ǉ�
void World::addLight(const ActorPtr& light) {
	light_ = light;
}

// �A�N�^�[�̒ǉ�
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

// �A�N�^�[�̌���
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}

std::forward_list<ActorPtr> World::findActors(const ActorGroup group)
{
	return actors_.GetActors(group);
}

// �t�B�[���h���ɑ��݂���A�N�^�[�O���[�v�̐����擾���܂�
int World::getActorCount(ActorGroup group)
{
	return actors_.getActorCount(group);
}

// �t�B�[���h�̎擾
FieldPtr World::getField() const {
	return field_;
}

// �Q�[���N���A���ǂ�����ݒ肵�܂�
void World::setIsGameClear(bool isClear)
{
	isClear_ = isClear;
}

// �Q�[���N���A���ǂ�����Ԃ��܂�
bool World::isGameClear()
{
	return isClear_;
}

// �����I�ɃQ�[���N���A�����邩��ݒ肵�܂�
void World::setIsGameClearEnd(bool isClearEnd)
{
	isClearEnd_ = isClearEnd;
}

// �����I�ɃQ�[���N���A���邩��Ԃ��܂�
bool World::isGameClearEnd()
{
	return isClearEnd_;
}

// ���b�Z�[�W�̑��M
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// �C�x���g���X�i�[�̒ǉ�
void World::addEventMessageListener(
	std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

