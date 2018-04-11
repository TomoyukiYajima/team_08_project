#include "TitleScener.h"
#include "../../Math/MathHelper.h"
//#include "../../Utility/ResourceLoader/ResourceLoader.h"
#include "../../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
//#include "../../Utility/Sound/SoundPlayer.h"
#include "../../Utility/Resource/Sound/Sound.h"
#include "../../Utility/Resource/ResourceLoader/ResourceID.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::start()
{
	isEnd_ = false;
	alphaTimer_ = 0.0f;
	kendoPositionX_ = -700.0f;
	karatePositionX_ = 700.0f;
	characterTexturePositionY_ = 100.0f;
	textureMoveSpeed_ = 80.0f;
	buttonAlpha_ = 1.0f;

	// BGMの再生
	Sound::play_bgm((int)SoundID::BGM_TITLE);
}

void TitleScene::update(float deltaTime)
{
	if (InputManager::GetInstance().IsKeyDown(KeyCode::SPACE)) {
		isEnd_ = true;
		Sound::play_se((int)SoundID::SE_SELECT);
		return;
	}

	alphaTimer_ += deltaTime;
	kendoPositionX_ += (textureMoveSpeed_ - 40.0f) * deltaTime;
	// 剣道画像のクランプ
	kendoPositionX_ = MathHelper::Clamp(
		kendoPositionX_, -1000, 275);
	karatePositionX_ += -(textureMoveSpeed_)* deltaTime;
	// 空手画像のクランプ
	karatePositionX_ = MathHelper::Clamp(
		karatePositionX_, -500, karatePositionX_);
	if ((int)alphaTimer_ % 20 < 10) buttonAlpha_ = 1.0f;
	else buttonAlpha_ = 0.0f;
}

void TitleScene::draw() const
{
	Graphics2D::draw_sprite((int)TextureID::TITLE_TEXTURE_TITLE, Vector2::Zero);
	Graphics2D::draw_sprite((int)TextureID::TITLE_TEXTURE_KENDO, Vector2(kendoPositionX_, characterTexturePositionY_));
	Graphics2D::draw_sprite((int)TextureID::TITLE_TEXTURE_KARATE, Vector2(karatePositionX_, characterTexturePositionY_));
	// ボタンの表示
	auto buttonPos = Vector2(1024 / 2, 768 - 60);
	auto size = Graphics2D::get_sprite_size((int)TextureID::TITLE_TEXTURE_OSU);
	auto center = Vector2(size.x / 2, size.y / 2);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(buttonAlpha_ * 255));
	SetDrawBright(0, 0, 0);
	Graphics2D::draw_sprite(
		(int)TextureID::TITLE_TEXTURE_OSU,
		buttonPos + Vector2::One * 5.0f, center, 1.0f, 1.0f, 0.0f, TRUE, 0);
	SetDrawBright(255, 255, 255);
	Graphics2D::draw_sprite(
		(int)TextureID::TITLE_TEXTURE_OSU,
		buttonPos, center, 1.0f, 1.0f, 0.0f, TRUE, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

bool TitleScene::isEnd() const
{
	return isEnd_;
}

Scene TitleScene::next() const
{
	return Scene::GamePlay;
}

void TitleScene::end()
{
	// BGMの停止
	Sound::stop_bgm();
}
