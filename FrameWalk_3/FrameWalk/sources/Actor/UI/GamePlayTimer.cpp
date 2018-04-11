#include "GamePlayTimer.h"
#include "../../Math/Color.h"
#include "../../Utility/Resource/ResourceLoader/ResourceID.h"
#include "../../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
#include "../../Utility/Resource/Graphic/Graphics2D/NumberTexture.h"

GamePlayTimer::GamePlayTimer() : 
	timer_(50.0f),
	textureNumber_(1){
}

GamePlayTimer::GamePlayTimer(float time, const Vector2 position, int textureNumber) :
	timer_(time * 60.0f),
	position_(position),
	textureNumber_(textureNumber){
}

void GamePlayTimer::update(float deltaTime) {
	timer_ -= deltaTime;
	if (timer_ < 0.0f) timer_ = 0.0f;
}

void GamePlayTimer::draw() const{
	// •¶Žš‚Ì•`‰æ
	// •`‰æ‚·‚é”Žš‚ÌˆÊ’u
	const Vector2 pos = Vector2(position_.x - 128.0f, position_.y);
	Vector2 shadowPos(pos.x + 5.0f, pos.y + 5.0f);
	// "ŽžŠÔ"‚Ì•`‰æ
	SetDrawBright(0, 0, 0);
	Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, shadowPos, 0.0f, 0.0f, 128.0f, 64.0f);
	SetDrawBright(255, 255, 255);
	Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, pos, 0.0f, 0.0f, 128.0f, 64.0f);
	// ”’l‚Ì•`‰æ
	static const NumberTexture number(textureNumber_, 32, 64);
	Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	if (timer_ < 10.0f * 60.0f && (int)timer_ % 60 >= 30)
		color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	// ŽžŠÔ
	if (timer_ != 0.0f)
		number.floatDraw(position_, timer_ / 60.0f * 10.0f, 3, color);
	else {
		shadowPos = Vector2(position_.x + 5.0f, position_.y + 5.0f);
		SetDrawBright(0, 0, 0);
		Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, shadowPos, 0.0f, 64.0f * 2, 128.0f, 64.0f);
		SetDrawBright((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255));
		Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, position_, 0.0f, 64.0f * 2, 128.0f, 64.0f);
		SetDrawBright(255, 255, 255);
	}
}

int GamePlayTimer::getTime() const{
	return timer_;
}

bool GamePlayTimer::getIsTimeOver() {
	return timer_ == 0.0f;
}
