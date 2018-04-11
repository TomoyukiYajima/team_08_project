#ifndef RESULT_H_
#define RESULT_H_

#include "../../Math/Vector2.h"
#include <vector>

class Result {
public:
	// コンストラクタ
	Result();
	// デストラクタ
	~Result();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// スコアをセットする
	void setScore();
	// 影の描画
	void drawShadow(const int textureNumber, const Vector2 position, const int x, const int y, const int w, const int h) const;

private:
	//Vector2 position_;
	// スコア
	int score_;
	// ランク
	int rank_;
	// シーン移行タイマ
	float changeSceneTimer_;
	// テクスチャの移動速度
	float moveSpeed_;
	// ボタンの透明度
	float buttonAlpha_;
	// 剣道部長画像の位置
	Vector2 kendoPosition_;
	// 評価コンテナ
	std::vector<float> rankContainer;
	// スコアコンテナ
	std::vector<int> scoreContainer;
};

#endif