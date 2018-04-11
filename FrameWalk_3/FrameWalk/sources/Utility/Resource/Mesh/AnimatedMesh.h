#ifndef ANIMATED_MESH_H_
#define ANIMATED_MESH_H_

#include "../../../Math/Matrix.h"
#include "../../Animation/ModelAnimation/ModelAnimation.h"

// �A�j���[�V�����t�����b�V���N���X
class AnimatedMesh {
public:
	// �R���X�g���N�^
	AnimatedMesh(int model, int motion = 0, bool loop = false);
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �`��(�����x�t��)
	void draw(float alpha) const;
	// �p���s��̐ݒ�
	void transform(const Matrix& matrix);
	// ���[�V�����̕ύX
	void change_motion(int motion, bool loop = false);
	// �{�[���̕ϊ��s����擾
	Matrix bone_matrix(int bone_no) const { return MV1GetFrameLocalWorldMatrix(model_, bone_no); }
	// �I�����Ԃ�Ԃ�
	float motion_end_time()const { return animation_.end_time(); }

private:
	// ���b�V��
	int model_;
	// �A�j���[�V����
	ModelAnimation animation_;
};

#endif