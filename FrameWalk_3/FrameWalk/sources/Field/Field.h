#ifndef FIELD_H_
#define FIELD_H_

//#include <gslib.h>
//class BoundingSphere;
//class Ray;
//class Line;
//#include <DxLib.h>
#include "../Math/Vector3.h"
#include "../Utility/Resource/ResourceLoader/ResourceID.h"

class Field {
public:
	// �R���X�g���N�^
	Field(const FieldID octree, const SkyID skybox, const float fieldSizeX, const float fieldSizeY);
	//// ���C�Ƃ̏Փ˔���
	//bool collision(
	//	const Ray& ray,
	//	GSvector3* intersect = nullptr,
	//	GSplane*   plane     = nullptr) const;
	//// ���C���Ƃ̏Փ˔���
	//bool collision(
	//	const Line& line,
	//	GSvector3* intersect = nullptr,
	//	GSplane*   plane = nullptr) const;
	//// ���̂Ƃ̏Փ˔���
	//bool collistion(
	//	const BoundingSphere& sphere,
	//	GSvector3* intersect = nullptr) const;
	// �`��
	void draw() const;
	// �t�B�[���h�n���h���̎擾
	int getFieldHendle();
	// �t�B�[���h�����H
	bool isInside(const Vector3& position) const;
	// �t�B�[���h�����H(�ʒu���Z�p)
	bool isInside(const Vector3& position, const Vector3& addFieldSize) const;
	// �t�B�[���h�O���H
	bool isOutside(const Vector3& position) const;
	// �t�B�[���h�O���H(�ʒu���Z�p)
	bool isOutside(const Vector3& position, const Vector3& addFieldSize) const;
	// �t�B�[���h�̑傫����Ԃ��܂�
	Vector3 getFieldScale();
	// �R�s�[�֎~
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;

private:
	float fieldSizeX_;
	float fieldSizeZ_;
	// �I�N�c���[
	FieldID octree_;
	// �X�J�C�{�b�N�X
	SkyID skybox_;
};

#endif
