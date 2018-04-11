#ifndef GRAPHICS_3D_H_
#define GRAPHICS_3D_H_

#include "../../../../Math/Matrix.h"
#include "../../../../Math/Vector3.h"
#include "../../../../Math/Color.h"

//���C�g�\����
struct Light {
	enum class Type {
		Directional,	// ��������
		Point,			// �|�C���g���C�g
		Spot			// �X�|�b�g���C�g
	};
	Type type{ Type::Directional };				// ���C�g�̃^�C�v
	Vector3 direction{ 1.0f, -1.0f, 1.0f };		// ���C�g�̕���
	Vector3 position{ Vector3::Zero };			// ���C�g�̍��W
	Color ambient{ 0.3f, 0.3f, 0.3f, 1.0f };	// ����
	Color diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };	// �g�U���ˌ�
	Color specular{ 1.0f, 1.0f, 1.0f, 1.0f };	// ���ʔ��ˌ�
	float attenuation0{ 0.1f };					// �����p�����[�^�P
	float attenuation1{ 0.1f };					// �����p�����[�^�Q
	float attenuation2{ 0.1f };					// �����p�����[�^�R
	float range{ 2000.0f };						// ���C�g�̉e���͈�
	float out_angle{ 114.0f };					// �X�|�b�g���C�g�̊O���̊p�x
	float in_angle{ 114.0f };					// �X�|�b�g���C�g�̓����̊p�x
};

// �u�����h���[�h
enum class BlendMode {
	None,	// ����
	Alpha,	// �A���t�@�u�����h
	Add,	// ���Z
	Sub		// ���Z
};

// 3D�O���t�B�b�N�N���X
class Graphics3D {
public:
	// ������
	static void initialize();
	// �I��
	static void finalize();

	// �X�N���[���̏���
	static void clear();
	// �X�N���[���̏����J���[�̐ݒ�
	static void clear_color(float r, float g, float b);

	// �r���[�|�[�g�̐ݒ�
	static void viewport(int x, int y, int w, int h);
	// ����ϊ��s��̐ݒ�
	static void view_matrix(const Matrix& view);
	// �����ϊ��s��̐ݒ�
	static void projection_matrix(const Matrix& projection);
	// ����ϊ��s��̎擾
	static Matrix view_matrix();
	// �����ϊ��s��̎擾
	static Matrix projection_matrix();

	// ���C�g�̐ݒ�
	static void light(const Light& light);
	// ���C�g�̎擾
	static Light light();
	// ���C�e�B���O��L���ɂ���
	static void enable_lighting();
	// ���C�e�B���O�𖳌��ɂ���
	static void disable_lighting();
	// Z�o�b�t�@��L���ɂ���
	static void enable_z_buffer();
	// Z�o�b�t�@�𖳌��ɂ���
	static void disable_z_buffer();
	// Z�o�b�t�@�̏������݂��s��
	static void enable_write_z_buffer();
	// Z�o�b�t�@�ɏ������݂��s��Ȃ�
	static void disable_write_z_buffer();

	// �u�����h���[�h�̐ݒ�
	static void blend_mode(BlendMode mode, float a = 1.0f);

private:
	// ���C�g�̐ݒ�
	static Light light_;
};

#endif