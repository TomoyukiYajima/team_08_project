#ifndef QUATERNION_H_
#define QUATERNION_H_

struct Vector3;
struct Matrix;

// クオータニオン(四元数)クラス
struct Quaternion {
	float x;		// x成分
	float y;		// y成分
	float z;		// z成分
	float w;		// w成分

	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	Quaternion(const Vector3& axis, float angle);
	// クオータニオンを正規化します
	static Quaternion Normalize(const Quaternion& q);
	// クオータニオンを正規化します
	Quaternion& Normalize();
	// クオータニオン同士の内積を求めます
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	// ノルムを求めます
	float Length() const;
	// 球面線形補間
	static Quaternion Slerp(const Quaternion& value1, const Quaternion& value2, float amount);
	//回転行列からクオータニオンを作成します
	static Quaternion CreateFromRotationMatrix(const Matrix& m);
};

// 単項演算子オーバーロード
Quaternion operator-(const Quaternion& q);

// 代入演算子オーバーロード
Quaternion& operator+=(Quaternion& q1, const Quaternion& q2);
Quaternion& operator-=(Quaternion& q1, const Quaternion& q2);
Quaternion& operator*=(Quaternion& q, float s);
Quaternion& operator/=(Quaternion& q, float s);
Quaternion& operator*=(Quaternion& q1, const Quaternion& q2);

// ２項演算子オーバーロード
Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
Quaternion operator*(const Quaternion& q, float s);
Quaternion operator*(float s, const Quaternion& q);
Quaternion operator/(const Quaternion& q, float s);

#endif