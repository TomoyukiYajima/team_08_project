#ifndef SCORE_H_
#define SCORE_H_

#include "../../Math/Vector2.h"

// スコアクラス
class Score {
public:
	// コンストラクタ
	explicit Score(int score = 0);
	// コンストラクタ
	Score(int score, const Vector2& position, const int textureNumber);
	// スコアの加算
	void add(int score);
	// スコアの描画
	void draw() const;
	// スコアの取得
	int get() const;

private:
	// スコア
	int score_;
	// テクスチャ番号
	int textureNumber_;
	// 位置
	Vector2 position_;
};

#endif

