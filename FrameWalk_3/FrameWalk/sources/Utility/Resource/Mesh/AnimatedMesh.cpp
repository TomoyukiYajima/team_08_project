#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(int model, int motion, bool loop) :
	model_(model),
	animation_{ model, motion, loop } {	}

void AnimatedMesh::update(float deltaTime)
{
	animation_.update(deltaTime);
}

void AnimatedMesh::draw() const
{
	MV1DrawModel(model_);
}

void AnimatedMesh::draw(float alpha) const
{
	MV1SetOpacityRate(model_, alpha);
	MV1DrawModel(model_);
}

void AnimatedMesh::transform(const Matrix & matrix)
{
	MV1SetMatrix(model_, matrix);
}

void AnimatedMesh::change_motion(int motion, bool loop)
{
	animation_.change_motion(motion, loop);
}
