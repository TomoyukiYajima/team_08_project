#ifndef MODEL_ANIMATION_H_
#define MODEL_ANIMATION_H_

#include "DxLib.h"

struct Vector3;

class ModelAnimation {
public:
	// �R���X�g���N�^
	ModelAnimation(int model, int motion, bool loop = false);
	// �X�V
	void update(float deltaTime);
	// ���[�V�����̕ύX
	void change_motion(int motion, bool loop = false);
	// ���ݍĐ����̃��[�V����
	int motion() const { return motion_; }
	// �{�[����Ԃ�
	int bone_count() const { return MV1GetFrameNum(model_); }
	// �I�����Ԃ�Ԃ�
	float end_time() const { return MV1GetAttachAnimTotalTime(model_, index_); }

	//// �A�j���[�V�����̕ύX�����܂�
	//void change(
	//	const int number, const bool isLoop = true, const float speed = 1.0f
	//	);
	//// �Đ����x�̕ύX���܂�
	//void changeSpeed(const float speed);
	//// �A�j���[�V�����̌��݂̎��Ԃ��擾���܂�
	//float getAnimationTime();
	//// �A�j���[�V�������I����������Ԃ��܂�
	//bool isEndAnimation();

	//void RotationYModel(const float degree);

private:
	// ���f���n���h��
	int model_{ -1 };
	// �Đ����̃A�j���[�V����
	int motion_{ -1 };
	// �A�^�b�`���̃C���f�b�N�X
	int index_{ -1 };
	// �Đ����̃A�j���[�V�����^�C�}
	float motion_timer_{ 0.0f };

	// �O�̃��f���n���h��
	int prev_model_{ -1 };
	// �O�̍Đ����̃A�j���[�V����
	int prev_motion_{ -1 };
	// �O�̃A�^�b�`���̃C���f�b�N�X
	int prev_index_{ -1 };
	// �O�̍Đ����̃A�j���[�V�����^�C�}
	float prev_motion_timer_{ 0.0f };

	// ��ԃ^�C�}
	float lerp_timer_{ 0.0f };
	// ���[�v�t���O
	bool is_loop_{ false };
	// ��ԃ^�C�}
	const float LerpTime{ 10.0f };
};

#endif