#include "Skydome.h"
#include <DxLib.h>

int SkyDome::handle_{ -1 };
//SkyDome::SkyDome(const SkyID id)
//{
//	//handle_ = ResourceLoader::GetInstance().getSkyID(id);
//}

void SkyDome::bind(const SkyID id)
{
	//handle_ = ResourceLoader::GetInstance().getSkyID(id);
}

void SkyDome::draw()
{
	//// �J�����̈ʒu�ɃX�J�C�h�[�����ړ�������
	//auto camera = world_->findActor("Camera");
	//auto position = Vector3::Zero;
	//if (camera != nullptr) position = camera->getPosition();
	//MV1SetPosition(handle_, position);
	//MV1DrawModel(handle_);

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
	MV1SetWriteZBuffer(handle_, false);
	// ���f���̕\��
	MV1DrawModel(handle_);
	// ����ϊ������ɖ߂�
	SetCameraViewMatrix(view_matirx);
	// ���C�e�B���O������L��������
	SetUseLighting(TRUE);
}
