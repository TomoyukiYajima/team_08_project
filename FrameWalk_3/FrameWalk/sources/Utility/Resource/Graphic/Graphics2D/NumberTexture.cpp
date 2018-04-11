#include "NumberTexture.h"
#include "../Graphics2D/Graphics2D.h"
#include <sstream>
#include <iomanip>

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
NumberTexture::NumberTexture(int texture, int width, int height) :
	texture_(texture),
	width_(width),
	height_(height),
	shadowPosition_(4, 4){
}

// •`‰æ
void NumberTexture::draw(const Vector2 & position, int num, int digit, char fill) const {
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << num;
	draw(position, ss.str());
}

// •`‰æ
void NumberTexture::draw(const Vector2 & position, int num) const {
	draw(position, std::to_string(num));
}

// •`‰æ
void NumberTexture::draw(const Vector2 & position, const std::string & num) const {
	for (int i = 0; i < (int)num.size(); ++i) {
		if (num[i] == ' ') continue;
		const int n = num[i] - '0';	
		// •`‰æ‚·‚é”š‚ÌˆÊ’u
		const Vector2 pos = Vector2(position.x + i * width_, position.y);
		// ‰e‚Ì•`‰æ
		drawShadow(pos, n * width_, 0.0f, width_, height_);
		Graphics2D::draw_sprite(texture_, pos, n * width_, 0.0f, width_, height_);
	}
}

// •`‰æ(float)
void NumberTexture::floatDraw(const Vector2& position, int num, int digit, const Color& color, char fill) const {
	std::stringstream ss;
	// ‚×‚«æ‚Ì”’l‚ğó‚¯æ‚Á‚ÄA’²®‚·‚é‚æ‚¤‚É‚·‚é
	ss << std::setw(digit) << std::setfill(fill) << num;
	floatDraw(position, ss.str(), digit, color);
}
// •`‰æ(float)
void NumberTexture::floatDraw(const Vector2& position, const std::string& num, int digit, const Color& color) const {
	for (int i = 0; i < (int)num.size(); ++i) {
		if (num[i] == ' ') continue;
		const int n = num[i] - '0';
		Vector2 pos(position.x + i * width_, position.y);
		// ¬”‚È‚çƒRƒ“ƒ}‚Ì•`‰æ
		if (i == digit - 1) {
			// ‰e‚Ì•`‰æ
			drawShadow(pos, 10 * width_, 0.0f, width_, height_);
			// •`‰æ
			SetDrawBright((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255));
			Graphics2D::draw_sprite(texture_, pos, 10 * width_, 0.0f, width_, height_);
			SetDrawBright(255, 255, 255);
			pos = { position.x + (i + 1) * width_ - width_ / 2.0f , position.y };
		}
		// ‰e‚Ì•`‰æ
		drawShadow(pos, n * width_, 0.0f, width_, height_);
		// •`‰æ
		SetDrawBright((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255));
		Graphics2D::draw_sprite(texture_, pos, n * width_, 0.0f, width_, height_);
		SetDrawBright(255, 255, 255);
	}
}

// ‰e‚Ì•`‰æ
void NumberTexture::drawShadow(const Vector2& position, const int x, const int y, const int w, const int h) const {
	// ‰e‚Ì•`‰æ
	const Vector2 pos = Vector2(position.x + shadowPosition_.x, position.y + shadowPosition_.y);
	SetDrawBright(0, 0, 0);
	Graphics2D::draw_sprite(texture_, pos, x, y, w, h);
	SetDrawBright(255, 255, 255);
}
