#include "Score.h"
#include "../../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
#include "../../Utility/Resource/Graphic/Graphics2D/NumberTexture.h"
#include "../../Utility/Resource/ResourceLoader/ResourceID.h"
#include <cmath>
#include <algorithm>

// コンストラクタ
Score::Score(int score) : score_(score) {
}

// コンストラクタ
Score::Score(int score, const Vector2& position, const int textureNumber) :
	score_(score),
	position_(position),
	textureNumber_(textureNumber) {
}

// スコアの加算
void Score::add(int score)
{
	score_ = min(score_ + score, 999);
}

// スコアの描画
void Score::draw() const {
	static const NumberTexture number(textureNumber_, 32, 64);
	number.draw(position_, score_, 3);
	// 文字の描画
	// 描画する数字の位置
	const Vector2 pos(position_.x - 128.0f, position_.y);
	const Vector2 shadowPos(pos.x + 5.0f, pos.y + 5.0f);
	// 影の描画
	SetDrawBright(0, 0, 0);
	Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, shadowPos, 0.0f, 64.0f, 128.0f, 64.0f);
	SetDrawBright(255, 255, 255);
	Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, pos, 0.0f, 64.0f, 128.0f, 64.0f);
}

// スコアの取得
int Score::get() const {
	return score_;
}
