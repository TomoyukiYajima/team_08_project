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
	// コンストラクタ
	Field(const FieldID octree, const SkyID skybox, const float fieldSizeX, const float fieldSizeY);
	//// レイとの衝突判定
	//bool collision(
	//	const Ray& ray,
	//	GSvector3* intersect = nullptr,
	//	GSplane*   plane     = nullptr) const;
	//// ラインとの衝突判定
	//bool collision(
	//	const Line& line,
	//	GSvector3* intersect = nullptr,
	//	GSplane*   plane = nullptr) const;
	//// 球体との衝突判定
	//bool collistion(
	//	const BoundingSphere& sphere,
	//	GSvector3* intersect = nullptr) const;
	// 描画
	void draw() const;
	// フィールドハンドルの取得
	int getFieldHendle();
	// フィールド内か？
	bool isInside(const Vector3& position) const;
	// フィールド内か？(位置加算用)
	bool isInside(const Vector3& position, const Vector3& addFieldSize) const;
	// フィールド外か？
	bool isOutside(const Vector3& position) const;
	// フィールド外か？(位置加算用)
	bool isOutside(const Vector3& position, const Vector3& addFieldSize) const;
	// フィールドの大きさを返します
	Vector3 getFieldScale();
	// コピー禁止
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;

private:
	float fieldSizeX_;
	float fieldSizeZ_;
	// オクツリー
	FieldID octree_;
	// スカイボックス
	SkyID skybox_;
};

#endif
