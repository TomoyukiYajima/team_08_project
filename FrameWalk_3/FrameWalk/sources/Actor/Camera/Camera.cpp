#include "Camera.h"
#include "../../World/IWorld.h"

// �R���X�g���N�^
Camera::Camera(IWorld* world) :
	Actor(world, "Camera", Vector3(0.0f, 0.0f, 0.0f)) {
}

// ������
void Camera::initialize()
{
	// �v���[��������
	auto player = world_->findActor("Player");
	// �v���[�������Ȃ�
	if (player == nullptr) return;
	// �v���[���̍��W���擾
	position_ = player->getPosition();
	// �v���[���̉�]�i�����j���擾
	rotate_ = player->getRotate();

	// �J�����̈ʒu�ύX
	SetCameraPositionAndTarget_UpVecY(
		position_ - Vector3(0.0f, 2.0f, 0.0f),
		position_);
	SetCameraViewMatrix(rotate_);
}

// �X�V
void Camera::onUpdate(float deltaTime) {
	(void)deltaTime;
	//// �v���[��������
	//auto player = world_->findActor("Player");
	//// �v���[�������Ȃ�
	//if (player == nullptr) return;

	//// �v���[���̍��W���擾
	//position_ = player->getPosition() + GSvector3(0.0f, 2.0f, 0.0f);
	//// �v���[���̉�]�i�����j���擾
	//rotate_ = player->getRotate();

	//// �J�����̈ړ�
	//// �v���C���[�����ɉ�]����
	//if (gsGetKeyState(GKEY_D) == GS_TRUE) {

	//}
	//else if (gsGetKeyState(GKEY_A) == GS_TRUE) {

	//}
}

// �`��
void Camera::onDraw() const 
{
	/*glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(getPose().convertViewRH());*/
}
