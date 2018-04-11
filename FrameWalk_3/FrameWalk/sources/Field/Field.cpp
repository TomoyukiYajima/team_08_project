#include "Field.h"
#include <cmath>
#include "../Utility/Resource/ResourceLoader/ResourceLoader.h"
#include "Sky/Skydome.h"
//#include "Sky/Skybox.h"
//#include "Ray.h"
//#include "Line.h"
//#include "BoundigShphere.h"

//const float FIELD_SIZE_X = 150.0f;
//const float FIELD_SIZE_Y = 150.0f;

// �R���X�g���N�^
Field::Field(const FieldID octree, const SkyID skybox, const float fieldSizeX, const float fieldSizeY) :
	octree_(octree),
	skybox_(skybox),
	fieldSizeX_(fieldSizeX),
	fieldSizeZ_(fieldSizeY) {
	SkyDome::bind(skybox);
}

//// ���C�Ƃ̏Փ˔���
//bool Field::collision(
//	const Ray& ray,
//	GSvector3* intersect,
//	GSplane*   plane) const {
//	return gsOctreeCollisionRay(
//		gsGetOctree(octree_),
//		&ray.position, &ray.direction, intersect, plane) == GS_TRUE;
//}

//// ���C���Ƃ̏Փ˔���
//bool Field::collision(
//	const Line& line,
//	GSvector3* intersect,
//	GSplane*   plane) const {
//	return gsOctreeCollisionLine(
//		gsGetOctree(octree_),
//		&line.start, &line.end, intersect, plane) == GS_TRUE;
//}

//// ���̂Ƃ̏Փ˔���
//bool Field::collistion(
//	const BoundingSphere& sphere,
//	GSvector3* intersect) const {
//	return gsOctreeCollisionSphere(
//		gsGetOctree(octree_),
//		&sphere.center, sphere.radius, intersect) == GS_TRUE;
//}

// �`��
void Field::draw() const {
	auto field = ResourceLoader::GetInstance().getFieldID(octree_);
	MV1SetPosition(field, Vector3::Zero);
	MV1DrawModel(field);
	SkyDome::draw();
	/*auto sky = ResourceLoader::GetInstance().getSkyID(skybox_);
	MV1SetPosition(sky, Vector3::Zero);
	MV1DrawModel(sky);*/
}

int Field::getFieldHendle()
{
	return ResourceLoader::GetInstance().getFieldID(octree_);
}

// �t�B�[���h�����H
bool Field::isInside(const Vector3& position) const {
	if (std::abs(position.x) >= fieldSizeX_) return false;
	if (std::abs(position.z) >= fieldSizeZ_) return false;
	return true;
}

// �t�B�[���h�����H(�ʒu���Z�p)
bool Field::isInside(const Vector3& position, const Vector3& addFieldSize) const {
	if (std::abs(position.x) >= fieldSizeX_ + addFieldSize.x) return false;
	if (std::abs(position.z) >= fieldSizeZ_ + addFieldSize.z) return false;
	return true;
}

// �t�B�[���h�O���H
bool Field::isOutside(const Vector3& position) const {
	return !isInside(position);
}

// �t�B�[���h�O���H(�ʒu���Z�p)
bool Field::isOutside(const Vector3& position, const Vector3& addFieldSize) const {
	return !isInside(position , addFieldSize);
}

// �t�B�[���h�̑傫����Ԃ��܂�
Vector3 Field::getFieldScale() {
	return Vector3(fieldSizeX_, 0.0f, fieldSizeZ_);
}
