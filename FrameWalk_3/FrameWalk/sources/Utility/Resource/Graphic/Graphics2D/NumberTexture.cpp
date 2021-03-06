#include "NumberTexture.h"
#include "../Graphics2D/Graphics2D.h"
#include <sstream>
#include <iomanip>

// コンストラクタ
NumberTexture::NumberTexture(int texture, int width, int height) :
	texture_(texture),
	width_(width),
	height_(height),
	shadowPosition_(4, 4){
}

// 描画
void NumberTexture::draw(const Vector2 & position, int num, int digit, char fill) const {
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << num;
	draw(position, ss.str());
}

// 描画
void NumberTexture::draw(const Vector2 & position, int num) const {
	draw(position, std::to_string(num));
}

// 描画
void NumberTexture::draw(const Vector2 & position, const std::string & num) const {
	for (int i = 0; i < (int)num.size(); ++i) {
		if (num[i] == ' ') continue;
		const int n = num[i] - '0';	
		// 描画する数字の位置
		const Vector2 pos = Vector2(position.x + i * width_, position.y);
		// 影の描画
		drawShadow(pos, n * width_, 0.0f, width_, height_);
		Graphics2D::draw_sprite(texture_, pos, n * width_, 0.0f, width_, height_);
	}
}

// 描画(float)
void NumberTexture::floatDraw(const Vector2& position, int num, int digit, const Color& color, char fill) const {
	std::stringstream ss;
	// べき乗の数値を受け取って、調整するようにする
	ss << std::setw(digit) << std::setfill(fill) << num;
	floatDraw(position, ss.str(), digit, color);
}
// 描画(float)
void NumberTexture::floatDraw(const Vector2& position, const std::string& num, int digit, const Color& color) const {
	for (int i = 0; i < (int)num.size(); ++i) {
		if (num[i] == ' ') continue;
		const int n = num[i] - '0';
		Vector2 pos(position.x + i * width_, position.y);
		// 小数ならコンマの描画
		if (i == digit - 1) {
			// 影の描画
			drawShadow(pos, 10 * width_, 0.0f, width_, height_);
			// 描画
			SetDrawBright((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255));
			Graphics2D::draw_sprite(texture_, pos, 10 * width_, 0.0f, width_, height_);
			SetDrawBright(255, 255, 255);
			pos = { position.x + (i + 1) * width_ - width_ / 2.0f , position.y };
		}
		// 影の描画
		drawShadow(pos, n * width_, 0.0f, width_, height_);
		// 描画
		SetDrawBright((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255));
		Graphics2D::draw_sprite(texture_, pos, n * width_, 0.0f, width_, height_);
		SetDrawBright(255, 255, 255);
	}
}

// 影の描画
void NumberTexture::drawShadow(const Vector2& position, const int x, const int y, const int w, const int h) const {
	// 影の描画
	const Vector2 pos = Vector2(position.x + shadowPosition_.x, position.y + shadowPosition_.y);
	SetDrawBright(0, 0, 0);
	Graphics2D::draw_sprite(texture_, pos, x, y, w, h);
	SetDrawBright(255, 255, 255);
}
