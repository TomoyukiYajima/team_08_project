#ifndef GRAPHICS_2D_H_
#define GRAPHICS_2D_H_

#include "../../../../Math/Vector2.h"
#include "../../../Animation/AnimatedSprite.h"
#include <string>
#include <unordered_map>

// �O���t�B�b�N�X�N���X
class Graphics2D {
public:
	// ������
	static void initialize();
	// �摜�t�@�C���̓ǂݍ���
	static void load_sprite(int id, const std::string& file_name);
	// �摜�t�@�C���̓ǂݍ���(�����w�肠��)
	static void load_sprite(int id, const std::string& file_name, int row, int column);
	// �`��(�摜�S��)
	static void draw_sprite(int id, const Vector2& position);
	// �`��(�摜�̈ꕔ����`��)
	static void draw_sprite(int id, const Vector2& position, int x, int y, int w, int h);
	// �`��(�g��k���Ȃ�)
	static void draw_sprite(int id, const Vector2& position, const Vector2& center, 
		int scaleX, int scaleY, int angle, int Trans, int Turn);
	// �`��(�����ԍ��w��)
	static void draw_sprite(int id, int div_no, const Vector2& position,
		const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
	// �`��(�A�j���[�V�����w��)
	static void draw_sprite(int id, int animation, float timer, const Vector2& position,
		const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
	// �A�j���[�V�����̒ǉ�
	static void add_sprite_animation(int id, int animation, int start, int end, float time);
	// �L�[�t���[����ǉ�
	static void add_sprite_key_frame(int id, int animation, float time, int div_no);
	// �L�[�t���[����ǉ�
	static void add_sprite_key_frame(int id, int animation, float time, int x, int y, int w, int h);
	// �X�v���C�g�̍폜
	static void delete_sprite(int id);
	// �A�j���[�V�����̏I�����Ԃ��擾
	static float get_sprite_animation_end_time(int id, int animation);
	// �e�N�X�`���̃T�C�Y���擾���܂�
	static Vector2 get_sprite_size(int id);
	// �O���t�B�b�N�X�̏I������
	static void finalize();

private:
	// �X�v���C�g�f�[�^
	static std::unordered_map<int, AnimatedSprite> sprite_map_;
};

#endif