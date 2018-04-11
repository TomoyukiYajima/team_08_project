#ifndef STATIC_MESH_H_
#define STATIC_MESH_H_

#include <string>
#include "ModelAsset.h"
#include "../../../Math/Matrix.h"

// �X�^�e�B�b�N���b�V���N���X
class StaticMesh {
public:
	// ������
	static void initialize();
	// �I������
	static void finalize();
	// �ǂݍ���
	static bool load(int id, const std::string file_name);
	// �폜
	static void erase(int id);
	// �o�C���h
	static void bind(int id);
	// �`��
	static void draw();
	// ���[���h�ϊ��s���ݒ肷��
	static void transform(const Matrix& world);

private:
	// �o�C���h���̃��f��
	static int model_;
	// �{�[���̃��[���h�ϊ��s��
	static Matrix world_matrix_;
	// ���f���A�Z�b�g
	static ModelAsset asset_;
};

#endif