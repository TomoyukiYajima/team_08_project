#include "World.h"
#include "../Field/Field.h"

// コンストラクタ
World::World() :
	listener_([](EventMessage, void*) {}),
	isClear_(false),
	isClearEnd_(false){
}

// 更新
void World::update(float deltaTime) {
	actors_.update(deltaTime);
	camera_->update(deltaTime);
	//light_->update(deltaTime);
}

// 描画
void World::draw() const {
	camera_->draw();
	//light_->draw();
	field_->draw();
	actors_.draw();
}

// メッセージ処理
void World::handleMessage(EventMessage message, void* param) {
	// ワールドのメッセージ処理
	listener_(message, param);
	// アクターのメッセージ処理
	actors_.handleMessage(message, param);
	camera_->handleMessage(message, param);
	//light_->handleMessage(message, param);
}
 
// フィールドの追加
void World::addField(const FieldPtr& field) {
	field_ = field;
}

// カメラの追加
void World::addCamera(const ActorPtr& camera) {
	camera_ = camera;
}

// ライトの追加
void World::addLight(const ActorPtr& light) {
	light_ = light;
}

// アクターの追加
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

// アクターの検索
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}

std::forward_list<ActorPtr> World::findActors(const ActorGroup group)
{
	return actors_.GetActors(group);
}

// フィールド内に存在するアクターグループの数を取得します
int World::getActorCount(ActorGroup group)
{
	return actors_.getActorCount(group);
}

// フィールドの取得
FieldPtr World::getField() const {
	return field_;
}

// ゲームクリアかどうかを設定します
void World::setIsGameClear(bool isClear)
{
	isClear_ = isClear;
}

// ゲームクリアかどうかを返します
bool World::isGameClear()
{
	return isClear_;
}

// 強制的にゲームクリアをするかを設定します
void World::setIsGameClearEnd(bool isClearEnd)
{
	isClearEnd_ = isClearEnd;
}

// 強制的にゲームクリアするかを返します
bool World::isGameClearEnd()
{
	return isClearEnd_;
}

// メッセージの送信
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// イベントリスナーの追加
void World::addEventMessageListener(
	std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

