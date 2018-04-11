#include "GamePlayScene.h"
#include "../../Actor/Character/Player/Player.h"
#include "../../Actor/Character/Enemy/Enemy.h"
#include "../../Actor/Camera/TpsCamera.h"
#include "../../Actor/Base/EventMessage.h"

#include "../../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
#include "../../Utility/Resource/Graphic/Graphics3D/Graphics3D.h"
#include "../../Utility/Resource/Sound/Sound.h"
#include "../../Field/Field.h"
#include "../../Math/Random.h"

#include <iostream>
#include <fstream>
//#include "../../Utility/Sound/SoundPlayer.h"
//#include "../../Field/Sky/Skydome.h"

GamePlayScene::GamePlayScene()
{
}

GamePlayScene::~GamePlayScene()
{
}

void GamePlayScene::start()
{
	isEnd_ = false;
	isGameOver_ = false;
	// 敵を20体まで生成
	enemyCreateCount_ = 20;

	// ここでワールドを追加するので、コンストラクタに移動上限を入れるようにする
	world_ = std::make_shared<World>();
	world_->addEventMessageListener(
		[=](EventMessage msg, void* param) {
		handleMessage(msg, param);
	}
	);
	// プレイヤーの追加
	auto player = std::make_shared<Player>(
		world_.get(), Vector3(0.0f, 10.0f, 0.0f));
	world_->addActor(ActorGroup::Player, player);
	// フィールドの追加
	world_->addField(std::make_shared<Field>(FieldID::KOUTEI_FIELD, SkyID::KOUTEI_SKYBOX, 20.0f, 20.0f));
	// カメラの追加
	auto camera = std::make_shared<TpsCamera>(
		world_.get(), Vector3(0.0f, 0.91f, 0.0f));
	world_->addCamera(camera);

	// スコア
	score_ = Score(0, Vector2(500, 30), (int)TextureID::TEXRUER_SCORE);
	// 制限時間 60秒
	gameTimer_ = GamePlayTimer(60.0f, Vector2(850, 30), (int)TextureID::TEXRUER_SCORE);
	// ミニマップ
	miniMap_ = MiniMap(world_.get(), Vector2(30.0f, 30.0f), 7.0f);
	// リザルト
	result_ = Result();

	// BGMの再生
	Sound::play_bgm((int)SoundID::BGM_STAGE1);

	auto light = Graphics3D::light();
	light.ambient = Color(0.5f, 0.5f, 0.5f, 1.0f);
	Graphics3D::light(light);
}

void GamePlayScene::update(float deltaTime)
{
	auto time = deltaTime;
	if (isGameOver_) {
		time = 0.0f;
		result_.update(deltaTime);
		// ボタンが押されたら、タイトルに戻る
		if (InputManager::GetInstance().IsKeyDown(KeyCode::SPACE)) {
			Sound::play_se((int)SoundID::SE_ATTACK1);
			isEnd_ = true;
			return;
		}
	}

	if (gameTimer_.getIsTimeOver()) return;
	world_->update(time);

	// 敵生成
	if (enemyCreateCount_ > 0) enemyCreate();

	gameTimer_.update(deltaTime);
	miniMap_.update(deltaTime);

	if (!gameTimer_.getIsTimeOver()) return;
	isGameOver_ = true;
	// スコアを渡す
	int rankingScore = score_.get();
	std::ofstream save_file("./resources/rankScore.txt");
	save_file << rankingScore;
	result_.setScore();
	Sound::stop_bgm();
	Sound::play_bgm((int)SoundID::BGM_ED);
}

void GamePlayScene::draw() const
{
	world_->draw();
	score_.draw();
	gameTimer_.draw();
	miniMap_.draw();
	if (!isGameOver_) return;
	result_.draw();
}

bool GamePlayScene::isEnd() const
{
	return isEnd_;
}

Scene GamePlayScene::next() const
{
	return Scene::Title;
}

void GamePlayScene::end()
{
	world_ = nullptr;
	// 全てのサウンドの停止
	Sound::stop_bgm();
}

// メッセージ処理
void GamePlayScene::handleMessage(EventMessage message, void* param) {
	int* value = (int*)param;
	switch (message)
	{
	case EventMessage::AddScore:
		score_.add(*value);
		break;
	case EventMessage::AddEnemyCount:
		enemyCreateCount_ += *value;
		break;
	}
}

// 敵生成関数
void GamePlayScene::enemyCreate() {
	auto fieldScale = world_->getField()->getFieldScale();
	int createCount = Random::rand(0, 1 + 1);
	float x, z;
	if (createCount % 2 == 0) {
		// Xランダム
		x = Random::rand(-fieldScale.x, fieldScale.x);
		createCount = Random::rand(0, 1 + 1);
		if (createCount % 2 == 0)
			z = -fieldScale.z;
		else z = fieldScale.z;
	}
	else {
		z = Random::rand(-fieldScale.x, fieldScale.x);
		createCount = Random::rand(0, 1 + 1);
		if (createCount % 2 == 0)
			x = -fieldScale.x;
		else x = fieldScale.x;
	}
	auto position = Vector3(x, 2.0f, z);
	auto enemy = std::make_shared<Enemy>(world_.get(), position);
	world_->addActor(ActorGroup::Enemy,enemy);
}

// 条件
int GamePlayScene::rankCount() {
	return 0;
}
