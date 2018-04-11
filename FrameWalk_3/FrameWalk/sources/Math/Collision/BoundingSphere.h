#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include "../../Math/Math.h"

class BoundingSphere {
public:
	BoundingSphere(const Vector3& center, float radius);

	explicit BoundingSphere(float radius = 0.0f);

	BoundingSphere translate(const Vector3& position) const;

	BoundingSphere transform(const Matrix& matrix) const;

	bool intersects(const BoundingSphere& other) const;

	void draw(const Vector3& position) const;

public:
	// íÜêSç¿ïW
	Vector3	center;
	// îºåa
	float radius;
};

#endif