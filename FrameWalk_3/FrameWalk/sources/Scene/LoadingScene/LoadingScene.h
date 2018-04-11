#ifndef LOADING_SCENE_H_
#define LOADING_SCENE_H_

#include "../Base/IScene.h"

class LoadingScene : public IScene {
public:
	LoadingScene();
	virtual ~LoadingScene();
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
	virtual void end() override;

private:
	void loadModels();
	void loadSounds();
	void loadTextures();

private:
	int fontHandle_;
	bool isDraw_;
};

#endif