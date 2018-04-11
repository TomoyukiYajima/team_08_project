#include "ModelAnimation.h"
//#include "DxLib.h"
#include <cmath>
#include "../../../Math/Vector3.h"
#include "../../../Math/Matrix.h"

// �R���X�g���N�^
ModelAnimation::ModelAnimation(int model, int motion, bool loop) :
	model_(model) {
	// ���[�V�����̕ύX
	change_motion(motion, loop);
}

// �X�V
void ModelAnimation::update(float deltaTime) {
	// ��Ԓ��̏���
	if (prev_index_ != -1) {
		// �A�j���[�V�����̕��
		const float amount = lerp_timer_ / LerpTime;
		// �s�����`��Ԃ��ĕ�Ԃ��Ă���
		// ���܂�ɂ����[�V�������Ⴂ������ƁA���f�����ςɂȂ�
		// �s��P�ʂȂ̂ŁA������Ԃ��邱�Ƃ��\
		// ��O���� : ��ԋ �傫���قǂ��̃��[�V�����������o��
		MV1SetAttachAnimBlendRate(model_, prev_index_, 1.0f - amount);
		MV1SetAttachAnimBlendRate(model_, index_, amount);
		// ��ԏI���������̏���
		if (lerp_timer_ >= LerpTime) {
			// �Â��A�j���[�V�����̍폜
			MV1DetachAnim(model_, prev_index_);
			prev_index_ = -1;
		}
		// ��ԃ^�C�}���X�V
		lerp_timer_ = std::fmin(lerp_timer_ + deltaTime, LerpTime);
	}

	// �Đ�
	MV1SetAttachAnimTime(model_, index_, motion_timer_);
	// �A�j���[�V�����^�C�}�̍X�V
	// ��b 30f �ŏI���悤�ɂ���
	motion_timer_ += 0.5f * deltaTime;
	// ���[�v����ꍇ�́Afloat �̂��܂�̎��Ԃ�n��
	if (is_loop_) motion_timer_ = std::fmod(motion_timer_, end_time());
	motion_timer_ = std::fmin(motion_timer_, end_time());
}

// ���[�V�����̕ύX
void ModelAnimation::change_motion(int motion, bool loop) {
	// ���݂Ɠ������[�V�����̏ꍇ�́A�������Ȃ�
	if (motion_ == motion) return;
	// ��Ԓ��̑O��̃��[�V�������폜
	if (prev_index_ != -1) MV1DetachAnim(model_, prev_index_);

	// �O��̃��[�V������ݒ�
	prev_motion_ = motion_;
	prev_motion_timer_ = motion_timer_;
	prev_index_ = index_;

	// ���[�V�����̍X�V
	motion_ = motion;
	// �Â��A�j���[�V�������f�^�b�`
	//if (index_ != -1) MV1DetachAnim(model_, index_);
	// �V�����A�j���[�V�������A�^�b�`
	index_ = MV1AttachAnim(model_, motion);
	// ���[�V�������Ԃ̕ύX
	motion_timer_ = 0.0f;
	// ��ԃ^�C�}��������
	lerp_timer_ = 0.0f;
	// �A�j���[�V�����̍X�V
	//MV1SetAttachAnimTime(model_, index_, motion_timer_);
	MV1SetAttachAnimTime(model_, index_, 0.0f);
	// ���[�v�t���O��ݒ�
	is_loop_ = loop;
}

//ModelAnimation::ModelAnimation(const int id, const int number, const float speed) :
//	id_(id),
//	animeNum_(number),
//	attachNum_(0),
//	speed_(speed),
//	timer_(0.0f),
//	totalTimer_(0.0f),
//	isLoop_(true)
//{
//	// �A�j���[�V�����̃A�^�b�`
//	attachNum_ = MV1AttachAnim(id_, animeNum_, -1, FALSE);
//	//  MV1GetAnimNum(						int MHandle ) ;
//	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
//	totalTimer_ = MV1GetAttachAnimTotalTime(id_, attachNum_);
//}
//
//void ModelAnimation::update(float deltaTime)
//{
//	//auto id = ResourceLoader::GetInstance().getModelID(id_);
//	timer_ = min(timer_ += speed_ * deltaTime / 6, totalTimer_);
//	// ���Đ����Ԃ𒴂������̏���
//	if (timer_ >= totalTimer_) {
//		if (isLoop_) timer_ = 0.0f;
//		//else timer_ = totalTimer_;
//	}
//
//	// ���f���̈ʒu�X�V
//	//MV1SetPosition(id, Vector3::Vector3ToVECTOR(position_));
//	// �A�j���[�V�����̍Đ�
//	MV1SetAttachAnimTime(id_, attachNum_, timer_);
//}
//
//void ModelAnimation::draw(const Vector3 & position) const
//{
//	// ���f���̈ʒu�X�V
//	MV1SetPosition(id_, Vector3::Vector3ToVECTOR(position));
//	// ���f���̕`��
//	MV1DrawModel(id_);
//}
//
//void ModelAnimation::change(const int number, const bool isLoop, const float speed)
//{
//	// ����̃A�j���[�V�����Ȃ�ύX���Ȃ�
//	if (animeNum_ == number) return;
//	MV1DetachAnim(id_, attachNum_);
//	attachNum_ = MV1AttachAnim(id_, number);
//	animeNum_ = number;
//	speed_ = speed;
//	isLoop_ = isLoop;
//	timer_ = 0.0f;
//	totalTimer_ = MV1GetAttachAnimTotalTime(id_, attachNum_);
//}
//
//void ModelAnimation::changeSpeed(const float speed) { speed_ = speed; }
//
//float ModelAnimation::getAnimationTime() { return timer_; }
//
//bool ModelAnimation::isEndAnimation() { return timer_ >= totalTimer_; }
//
//void ModelAnimation::RotationYModel(const float degree)
//{
//	MV1SetRotationMatrix(
//		id_, 
//		Matrix::MatrixToMATRIX(Matrix::CreateRotationY(degree))
//		);
//}
