#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

#include "../../../../Math/Vector2.h"
#include "../../../../Math/Color.h"
#include <string>

class NumberTexture {
public:
	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	NumberTexture(int texture, int width, int height);
	// •`‰æ
	void draw(const Vector2& position, int num, int digit, char fill = '0') const;
	// •`‰æ
	void draw(const Vector2& position, int num) const;
	// •`‰æ
	void draw(const Vector2& position, const std::string& num) const;
	// •`‰æ(float)
	void floatDraw(const Vector2& position, int num, int digit, const Color& color, char fill = '0') const;
	// •`‰æ(float)
	void floatDraw(const Vector2& position, const std::string& num, int digit, const Color& color) const;
	// ‰e‚Ì•`‰æ
	void drawShadow(const Vector2& position, const int x, const int y, const int w, const int h) const;

private:
	// ƒeƒNƒXƒ`ƒƒ
	int	texture_;
	// •
	int		width_;
	// ‚‚³
	int		height_;
	// ‰e‚ÌˆÊ’u
	Vector2	shadowPosition_;
};

#endif

