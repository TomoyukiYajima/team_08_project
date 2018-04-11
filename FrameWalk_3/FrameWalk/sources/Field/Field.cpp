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

// コンストラクタ
Field::Field(const FieldID octree, const SkyID skybox, const float fieldSizeX, const float fieldSizeY) :
	octree_(octree),
	skybox_(skybox),
	fieldSizeX_(fieldSizeX),
	fieldSizeZ_(fieldSizeY) {
	SkyDome::bind(skybox);
}

//// レイとの衝突判定
//bool Field::collision(
//	const Ray& ray,
//	GSvector3* intersect,
//	GSplane*   plane) const {
//	return gsOctreeCollisionRay(
//		gsGetOctree(octree_),
//		&ray.position, &ray.direction, intersect, plane) == GS_TRUE;
//}

//// ラインとの衝突判定
//bool Field::collision(
//	const Line& line,
//	GSvector3* intersect,
//	GSplane*   plane) const {
//	return gsOctreeCollisionLine(
//		gsGetOctree(octree_),
//		&line.start, &line.end, intersect, plane) == GS_TRUE;
//}

//// 球体との衝突判定
//bool Field::collistion(
//	const BoundingSphere& sphere,
//	GSvector3* intersect) const {
//	return gsOctreeCollisionSphere(
//		gsGetOctree(octree_),
//		&sphere.center, sphere.radius, intersect) == GS_TRUE;
//}

// 描画
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

// フィールド内か？
bool Field::isInside(const Vector3& position) const {
	if (std::abs(position.x) >= fieldSizeX_) return false;
	if (std::abs(position.z) >= fieldSizeZ_) return false;
	return true;
}

// フィールド内か？(位置加算用)
bool Field::isInside(const Vector3& position, const Vector3& addFieldSize) const {
	if (std::abs(position.x) >= fieldSizeX_ + addFieldSize.x) return false;
	if (std::abs(position.z) >= fieldSizeZ_ + addFieldSize.z) return false;
	return true;
}

// フィールド外か？
bool Field::isOutside(const Vector3& position) const {
	return !isInside(position);
}

// フィールド外か？(位置加算用)
bool Field::isOutside(const Vector3& position, const Vector3& addFieldSize) const {
	return !isInside(position , addFieldSize);
}

// フィールドの大きさを返します
Vector3 Field::getFieldScale() {
	return Vector3(fieldSizeX_, 0.0f, fieldSizeZ_);
}
