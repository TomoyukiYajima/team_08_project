#ifndef GAMEPLAYTIMER_H_
#define GAMEPLAYTIMER_H_

#include "../../Math/Vector2.h"

class GamePlayTimer {
public:
	// コンストラクタ
	GamePlayTimer();
	// コンストラクタ
	GamePlayTimer(float time, const Vector2 position, int textureNumber);
	// 更新
	void update(float deltaTime);
	// タイムの描画
	void draw() const;
	// タイムの取得
	int getTime() const;
	// テクスチャ番号
	int textureNumber_;
	// 時間切れかどうかを取得
	bool getIsTimeOver();

private:
	 float timer_;

	 Vector2 position_;
};

#endif
