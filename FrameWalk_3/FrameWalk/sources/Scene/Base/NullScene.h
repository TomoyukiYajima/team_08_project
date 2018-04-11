#ifndef NULL_SCENE_H_
#define NULL_SCENE_H_

#include "IScene.h"

class NullScene : public IScene
{
public:
	virtual void start() override {}
	virtual void update(float deltaTime) override {}
	virtual void draw() const override {}
	virtual void end() override {}
	virtual bool isEnd() const override { return false; }
	virtual Scene next() const override { return Scene::Null; }
};

#endif

