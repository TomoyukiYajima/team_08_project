#include "LoadingScene.h"
#include "../../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
#include "../../Utility/Resource/Sound/Sound.h"
#include "../../Utility/Resource/ResourceLoader/ResourceLoader.h"
#include "../../Utility/Resource/Mesh/SkeletalMesh.h"
#include "../../Math/Random.h"

LoadingScene::LoadingScene()
{
	isEnd_ = false;
	isDraw_ = false;
}

LoadingScene::~LoadingScene()
{
	//ResourceLoader::GetInstance()
	//ResourceLoader::GetInstance().clearResources();
}

void LoadingScene::start()
{
	/*SkeletalMesh::initialize();
	Graphics2D::initialize();
	Sound::initialize();*/
	//ResourceLoader::GetInstance().
	// 乱数の生成
	Random::randomize();

	// フォントハンドルの生成
	fontHandle_ = CreateFontToHandle(NULL, 30, 30, DX_FONTTYPE_NORMAL);
}

void LoadingScene::update(float deltaTime)
{
	//// リソースの読み込み
	//if (isDraw_) {
	//	loadModels();
	//	loadSounds();
	//	loadTextures();

	//	isEnd_ = true;
	//}
	//
	//isDraw_ = true;
}

void LoadingScene::draw() const
{
	// 読み込み文字の描画
	DrawStringToHandle(1024 / 2 - 30 * 4, 768 / 2 - 30, "データ読み込み中", GetColor(255, 255, 255), fontHandle_);
}

bool LoadingScene::isEnd() const
{
	return isEnd_;
}

Scene LoadingScene::next() const
{
	return Scene::Title;
}

void LoadingScene::end()
{
	//DeleteFontToHandle(fontHandle_);
}

void LoadingScene::loadModels()
{
	// 地形
	ResourceLoader::GetInstance().loadField(
		FieldID::KOUTEI_FIELD, "./resources/octree/koutei_oct.mqo");
	// スカイドーム
	ResourceLoader::GetInstance().loadSky(
		SkyID::KOUTEI_SKYBOX, "./resources/sky/skydome.mqo");
	//// アニメーションも読み込まれる
	ResourceLoader::GetInstance().loadModel(ModelID::PLAYER_MODEL, "./resources/model/Kendo/kendo.mv1");
	ResourceLoader::GetInstance().loadModel(ModelID::ENEMY_MODEL, "./resources/model/Karate/Karate.mv1");
}

void LoadingScene::loadSounds()
{
	//BGM
	ResourceLoader::GetInstance().loadBGM(SoundID::SAMPLE_BGM, "./resources/sound/bgm/kendo.wav");
	ResourceLoader::GetInstance().loadBGM(SoundID::BGM_TITLE, "./resources/sound/bgm/kendo.wav");
	ResourceLoader::GetInstance().loadBGM(SoundID::BGM_STAGE1, "./resources/sound/bgm/kendo.wav");
	ResourceLoader::GetInstance().loadBGM(SoundID::BGM_ED, "./resources/sound/bgm/kendo.wav");
	ResourceLoader::GetInstance().loadBGM(SoundID::BGM_TIMEEND, "./resources/sound/bgm/kendo.wav");
	//Sound::load_bgm((int)SoundID::SAMPLE_BGM, "./resources/sound/bgm/kendo.wav");
	/*Sound::load_bgm((int)SoundID::BGM_TITLE, "./resources/sound/bgm/title.wav");
	Sound::load_bgm((int)SoundID::BGM_STAGE1, "./resources/sound/bgm/kendo.wav");
	Sound::load_bgm((int)SoundID::BGM_ED, "./resources/sound/bgm/ed.wav");
	Sound::load_bgm((int)SoundID::BGM_TIMEEND, "./resources/sound/bgm/timeend.wav");*/
	// SE
	ResourceLoader::GetInstance().loadSE(SoundID::SAMPLE_SE, "./resources/sound/se/Attack1.wav");
	ResourceLoader::GetInstance().loadSE(SoundID::SE_ATTACK1, "./resources/sound/se/Attack1.wav");
	ResourceLoader::GetInstance().loadSE(SoundID::SE_ATTACK2, "./resources/sound/se/Attack1.wav");
	ResourceLoader::GetInstance().loadSE(SoundID::SE_DAMAGE, "./resources/sound/se/Attack1.wav");
	ResourceLoader::GetInstance().loadSE(SoundID::SE_SELECT, "./resources/sound/se/Attack1.wav");
}

void LoadingScene::loadTextures()
{
	// スコア
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXRUER_SCORE, "./resources/texture/num.png");
	// ゲームプレイ
	ResourceLoader::GetInstance().loadTexture(TextureID::GAMEPLAY_TEXTURE_TEXTS, "./resources/texture/text.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::GAMEPLAY_TEXTURE_RADAR, "./resources/texture/radar.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::GAMEPLAY_TEXTURE_PT, "./resources/texture/pt.png");
	// タイトル
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_TEXTURE_TITLE, "./resources/texture/title.bmp");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_TEXTURE_KENDO, "./resources/texture/mini_kendo.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_TEXTURE_KARATE, "./resources/texture/mini_karate.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_TEXTURE_OSU, "./resources/texture/osu.png");
	// リザルト
	ResourceLoader::GetInstance().loadTexture(TextureID::RESULT_TEXTURE_BACKGROUND, "./resources/texture/blue.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::RESULT_TEXTURE_RESULT_1, "./resources/texture/result1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::RESULT_TEXTURE_RESULT_2, "./resources/texture/result2.png");
}
