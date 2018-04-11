#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Game.h"
#include "../Scene/Base/SceneManager.h"

class GameManager : public Game {
public:
	GameManager();
	~GameManager(){}
private:
	// 開始
	virtual void start() override;
	// 更新
	virtual void update() override;
	// 描画
	virtual void draw() override;
	// 終了
	virtual void end() override;

private:
	// シーンマネージャー
	SceneManager sceneManager_;
};

#endif
