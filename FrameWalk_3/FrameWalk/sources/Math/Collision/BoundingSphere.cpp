#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(const Vector3 & center, float radius) :
	center(center),
	radius(radius) {}

BoundingSphere::BoundingSphere(float radius) :
	BoundingSphere(Vector3(0.0f, 0.0f, 0.0f), radius) {}

BoundingSphere BoundingSphere::translate(const Vector3 & position) const
{
	return{ center + position, radius };
}

BoundingSphere BoundingSphere::transform(const Matrix & matrix) const
{
	return{ center * matrix, radius * matrix.Scale().y };
}

bool BoundingSphere::intersects(const BoundingSphere & other) const
{
	/*return
		(other.center.x - center.x) * (other.center.x - center.x) +
		(other.center.y - center.y) * (other.center.y - center.y) +
		(other.center.z - center.z) * (other.center.z - center.z) <=
		(radius + other.radius) * (radius + other.radius);*/
}

void BoundingSphere::draw(const Vector3& position) const
{
	DrawSphere3D(position, radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}
