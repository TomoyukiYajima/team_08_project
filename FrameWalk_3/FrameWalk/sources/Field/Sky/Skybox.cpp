#include "Skybox.h"
#include <DxLib.h>

// �o�C���h���̃��f��
int Skybox::model_{ -1 };
// ���f���A�Z�b�g
ModelAsset Skybox::asset_;

void Skybox::initialize()
{
	finalize();
}

void Skybox::finalize()
{
	asset_.clear();
}

bool Skybox::load(int id, const std::string file_name)
{
	return asset_.load(id, file_name);
}

void Skybox::erase(int id)
{
	asset_.erase(id);
	model_ = (model_ == id) ? -1 : model_;
}

void Skybox::bind(int id)
{
	model_ = asset_[id];
}

void Skybox::draw()
{
	// ����ϊ��s��̎擾
	MATRIX view_matirx = GetCameraViewMatrix();
	// ����ϊ��s��̕��s�ړ��ʂ��N���A
	MATRIX skybox_matrix = view_matirx;
	for (int i = 0; i != 3; ++i) {
		skybox_matrix.m[3][i] = 0.0f;
	}
	// ����ϊ��s��̐ݒ�
	SetCameraViewMatrix(skybox_matrix);
	// ���C�e�B���O�����𖳌��ɂ���
	SetUseLighting(FALSE);
	// Z�o�b�t�@�ɏ������݂��s��Ȃ�
	MV1SetWriteZBuffer(model_, false);
	// ���f���̕\��
	MV1DrawModel(model_);
	// ����ϊ������ɖ߂�
	SetCameraViewMatrix(view_matirx);
	// ���C�e�B���O������L��������
	SetUseLighting(TRUE);
}
