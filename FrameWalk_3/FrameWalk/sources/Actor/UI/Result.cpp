#include "Result.h"
#include "../../Math/MathHelper.h"
#include "../../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
#include "../../Utility/Resource/Graphic/Graphics2D/NumberTexture.h"
#include "../../Utility/Resource/ResourceLoader/ResourceID.h"
#include <iostream>
#include <fstream>

Result::Result() : 
	score_(0),
	rank_(0),
	changeSceneTimer_(0.0f),
	moveSpeed_(40.0f),
	buttonAlpha_(1.0f),
	kendoPosition_(0.0f, 100.0f)
{
	scoreContainer.clear();
	rankContainer.clear();
}

Result::~Result()
{
	scoreContainer.clear();
	rankContainer.clear();
}

void Result::update(float deltaTime)
{
	kendoPosition_.x += moveSpeed_ * deltaTime;
	kendoPosition_.x = MathHelper::Clamp(kendoPosition_.x, -1000, 375);
	// ボタンが押されたらタイトルに戻る
	changeSceneTimer_ += deltaTime;
	if ((int)changeSceneTimer_ % 20 < 10) buttonAlpha_ = 1.0f;
	else buttonAlpha_ = 0.0f;
}

void Result::draw() const
{
	Vector2 backgroundPos((1024 - 984.0f) / 2.0f, 100.0f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(0.5f * 255));
	Graphics2D::draw_sprite((int)TextureID::RESULT_TEXTURE_BACKGROUND, backgroundPos);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	// 剣道部長
	Graphics2D::draw_sprite((int)TextureID::TITLE_TEXTURE_KENDO, kendoPosition_);
	// 評価
	const Vector2 result1_pos(backgroundPos.x + 20.0f, backgroundPos.y + 10.0f);
	const Vector2 result2_pos(result1_pos.x + 20.0f, result1_pos.y + 60.0f);
	drawShadow((int)TextureID::RESULT_TEXTURE_RESULT_1, result1_pos, 0.0f, rankContainer[rank_], 1000.0f, 64.0f);
	SetDrawBright(255, 0, 0);
	Graphics2D::draw_sprite((int)TextureID::RESULT_TEXTURE_RESULT_1, result1_pos, 0.0f, rankContainer[rank_], 1000.0f, 64.0f);
	SetDrawBright(255, 255, 255);
	drawShadow((int)TextureID::RESULT_TEXTURE_RESULT_2, result2_pos, 0.0f, rankContainer[rank_ + 5], 916.0f, 150.0f);
	Graphics2D::draw_sprite((int)TextureID::RESULT_TEXTURE_RESULT_2, result2_pos, 0.0f, rankContainer[rank_ + 5], 916.0f, 150.0f);
	// 順位
	const float rankingRectY = 60.0f;
	const Vector2 rankingTextPosition = Vector2(result1_pos.x, result2_pos.y + 180.0f);
	// 順位の文字
	drawShadow((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, rankingTextPosition, 0.0f, 64.0f * 3.0f, 128.0f, 64.0f);
	Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, rankingTextPosition, 0.0f, 64.0f * 3.0f, 128.0f, 64.0f);
	// 順位のポイント
	int point = 0;
	std::ifstream loadfile("./resources/ranking.txt");
	static const NumberTexture number((int)TextureID::TEXRUER_SCORE, 32, 64);
	for (int i = 0; i != 5; ++i) {
		Vector2 rankingPosition(
			rankingTextPosition.x + 128.0f + 10.0f,
			rankingTextPosition.y + (rankingRectY * i));
		drawShadow((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, rankingPosition, 128.0f, rankingRectY * i, 256.0f, rankingRectY);
		Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_TEXTS, rankingPosition, 128.0f, rankingRectY * i, 256.0f, rankingRectY);
		// テキスト内の数値の読み込み
		loadfile >> point;
		const Vector2 rankingPointPosition(rankingPosition.x + 128.0f + 10.0f, rankingPosition.y);
 		number.draw(rankingPointPosition, point, 3);
	}
	// ボタンの描画
	Vector2 buttonPosition = Vector2(1024 / 4, 768 - 60);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(buttonAlpha_ * 255));
	SetDrawBright(0, 0, 0);
	Graphics2D::draw_sprite((int)TextureID::TITLE_TEXTURE_OSU, buttonPosition + Vector2::One * 5.0f);
	SetDrawBright(255, 255, 255);
	Graphics2D::draw_sprite((int)TextureID::TITLE_TEXTURE_OSU, buttonPosition);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Result::setScore()
{
	// 評価１の追加
	for (int i = 0; i != 5; ++i) {
		rankContainer.push_back(64.0f * 4 - 64.0f * i);
	}
	// 評価２の追加
	// 200.0f = 文字の４列
	for (int i = 0; i != 5; ++i) {
		rankContainer.push_back(200.0f * 4 - 200.0f * i);
	}
	// ランクスコア
	std::ifstream rankLoad_file("./resources/rankScore.txt");
	rankLoad_file >> score_;
	rank_ = score_ / 10;
	rank_ = MathHelper::Clamp(rank_, 0, 5 - 1);
	// スコアの更新
	int point = 0;
	int rankChangeCount = 0;
	std::ifstream scoreLoad_file("./resources/ranking.txt");
	for (int i = 0; i != 5; ++i) {
		// テキスト内の数値の読み込み
		scoreLoad_file >> point;
		// ポイントが上回っていたら、一回だけ上にスコアを更新する
		if (point <= score_ && rankChangeCount == 0) {
			scoreContainer.push_back(score_);
			rankChangeCount = 1;
		}
		scoreContainer.push_back(point);
	}
	// データのセーブ
	std::ofstream scoreSave_file("./resources/ranking.txt");
	for (int i = 0; i != 5; ++i) {
		// テキスト内の数値を更新する
		scoreSave_file << scoreContainer[i] << std::endl;
	}
}

// 影の描画
void Result::drawShadow(const int textureNumber, const Vector2 position, const int x, const int y, const int w, const int h) const {
	const Vector2 pos = Vector2(position.x + 5.0f, position.y + 5.0f);
	SetDrawBright(0, 0, 0);
	Graphics2D::draw_sprite(textureNumber, pos, x, y, w, h);
	SetDrawBright(255, 255, 255);
}
