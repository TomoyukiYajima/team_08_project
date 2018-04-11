#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

#include "../../../../Math/Vector2.h"
#include "../../../../Math/Color.h"
#include <string>

class NumberTexture {
public:
	// �R���X�g���N�^
	NumberTexture(int texture, int width, int height);
	// �`��
	void draw(const Vector2& position, int num, int digit, char fill = '0') const;
	// �`��
	void draw(const Vector2& position, int num) const;
	// �`��
	void draw(const Vector2& position, const std::string& num) const;
	// �`��(float)
	void floatDraw(const Vector2& position, int num, int digit, const Color& color, char fill = '0') const;
	// �`��(float)
	void floatDraw(const Vector2& position, const std::string& num, int digit, const Color& color) const;
	// �e�̕`��
	void drawShadow(const Vector2& position, const int x, const int y, const int w, const int h) const;

private:
	// �e�N�X�`��
	int	texture_;
	// ��
	int		width_;
	// ����
	int		height_;
	// �e�̈ʒu
	Vector2	shadowPosition_;
};

#endif

