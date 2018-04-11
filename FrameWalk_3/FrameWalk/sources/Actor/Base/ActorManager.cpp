#include "ActorManager.h"
#include "ActorGroup.h"

// コンストラクタ
ActorManager::ActorManager() {
	initialize();
}

// 初期化
void ActorManager::initialize() {
	actors_[ActorGroup::BuilDing] = std::make_shared<Actor>();
	actors_[ActorGroup::GimmickObject] = std::make_shared<Actor>();
	actors_[ActorGroup::Player] = std::make_shared<Actor>();
	actors_[ActorGroup::PlayerBullet] = std::make_shared<Actor>();
	actors_[ActorGroup::Enemy] = std::make_shared<Actor>();
	actors_[ActorGroup::EnemyBullet] = std::make_shared<Actor>();
	actors_[ActorGroup::Effect] = std::make_shared<Actor>();
	root_.clearChildren();
	// 描画順に追加
	root_.addChild(actors_[ActorGroup::Effect]);
	root_.addChild(actors_[ActorGroup::Player]);
	root_.addChild(actors_[ActorGroup::EnemyBullet]);
	root_.addChild(actors_[ActorGroup::PlayerBullet]);
	root_.addChild(actors_[ActorGroup::Enemy]);
	root_.addChild(actors_[ActorGroup::GimmickObject]);
	root_.addChild(actors_[ActorGroup::BuilDing]);
}

// 更新
void ActorManager::update(float deltaTime) {
	root_.update(deltaTime);
	collide();
	root_.removeChildren();
}

// 描画
void ActorManager::draw() const {
	root_.draw();
}

// アクターの追加
void ActorManager::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_[group]->addChild(actor);
	actor->setActorGroup(group);
}

// アクターの検索
ActorPtr ActorManager::findActor(const std::string& name) {
	return root_.findCildren(name);
}

// フィールド内に存在するアクターグループの数を取得します
int ActorManager::getActorCount(ActorGroup group)
{
	return actors_[group]->getActorCount();
}

//アクターをグループで取得します
std::forward_list<ActorPtr> ActorManager::GetActors(const ActorGroup group)
{
	return actors_[group]->getChildren();
}

// アクターのグループを変更します
void ActorManager::changeActorGroup(ActorGroup group, const ActorPtr & actor)
{
	// 追加
	actors_[group]->addChild(actor);
	// 
	auto actors = GetActors(group);
	for (auto i = actors.begin(); i != actors.end(); ++i) {
		auto ac = *i;
		if (ac != actor) continue;
		// 同一のアクター
		//actors_[ac->getActorGroup()]->removeChildren();
		actor->setActorGroup(group);
		break;
	}
}

// メッセージ処理
void ActorManager::handleMessage(EventMessage message, void* param) {
	root_.handleMessage(message, param);
}

// 衝突判定
void ActorManager::collide() {
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy]);
	//actors_[ActorGroup::Enemy]->collideChildren(*actors_[ActorGroup::Player]);
	//actors_[ActorGroup::Enemy]->collideChildren(*actors_[ActorGroup::Enemy]);
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::EnemyBullet]);
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::BuilDing]);
	actors_[ActorGroup::PlayerBullet]->collideChildren(*actors_[ActorGroup::Enemy]);
}
