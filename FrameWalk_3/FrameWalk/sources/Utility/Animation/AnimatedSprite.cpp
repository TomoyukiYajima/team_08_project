#include "AnimatedSprite.h"
#include "../../Math/MathHelper.h"
#include <cmath>
#include <DxLib.h>

AnimatedSprite::~AnimatedSprite()
{
	clear();
}

void AnimatedSprite::load(const std::string & file_name)
{
	// 古いデータを削除
	clear();
	// 画像の読み込み
	graph_ = LoadGraph(file_name.c_str());
}

void AnimatedSprite::load(const std::string & file_name, int row, int column)
{
	// 画像データの読み込み
	load(file_name);
	// 画像サイズの取得
	int size_x = 0, size_y = 0;
	GetGraphSize(graph_, &size_x, &size_y);

	// 画像の分割
	int w = size_x / column;
	int h = size_y / row;
	for (int y = 0; y < size_y; y += h) {
		for (int x = 0; x < size_x; x += w) {
			div_graphs_.push_back(DerivationGraph(x, y, w, h, graph_));
		}
	}
}

void AnimatedSprite::draw(const Vector2 & position) const
{
	DrawGraphF(position.x, position.y, graph_, TRUE);
}

void AnimatedSprite::draw(const Vector2 & position, int x, int y, int w, int h) const
{
	DrawRectGraphF(position.x, position.y, x, y, w, h, graph_, TRUE, FALSE);
}

void AnimatedSprite::draw(const Vector2 & position, const Vector2 & center, int scaleX, int scaleY, int angle, int Trans, int Turn) const
{
	DrawRotaGraph3(position.x, position.y, center.x, center.y,
		scaleX, scaleY, angle,
		graph_, Trans, Turn);
}

void AnimatedSprite::draw(int graph, const Vector2 & position, const Vector2 & center, const Vector2 & scale, float rotation) const
{
	DrawRotaGraph3F(position.x, position.y, center.x, center.y, scale.x, scale.y,
		MathHelper::ToRadius(rotation), div_graphs_[graph], TRUE);
}

void AnimatedSprite::draw(int animation, float time, const Vector2 & position, const Vector2 & center, const Vector2 & scale, float rotation) const
{
	draw(find_key_frame(animation, time).second, position, center, scale, rotation);
}

void AnimatedSprite::add_animation(int animation, int start, int end, float time)
{
	animations_[animation].clear();
	for (int frame = 0; frame <= (end - start); ++frame) {
		add_key_frame(animation, (frame + 1) * time, start + frame);
	}
}

void AnimatedSprite::add_key_frame(int animation, float time, int graph_no)
{
	animations_[animation].emplace_back(time, graph_no);
}

void AnimatedSprite::add_key_frame(int animation, float time, int x, int y, int w, int h)
{
	div_graphs_.push_back(DerivationGraph(x, y, w, h, graph_));
	add_key_frame(animation, time, int(div_graphs_.size()) - 1);
}

float AnimatedSprite::animation_end_time(int animation) const
{
	return animations_.at(animation).back().first;
}

Vector2 AnimatedSprite::get_sprite_size()
{
	int x, y, flag;
	//テクスチャのサイズ取得
	flag = GetGraphSize(graph_, &x, &y);
	if (flag < 0) return Vector2::Zero;

	return Vector2(static_cast<float>(x), static_cast<float>(y));
}

void AnimatedSprite::clear()
{
	if (graph_ != -1) {
		DeleteSharingGraph(graph_);
		graph_ = -1;
		div_graphs_.clear();
	}
	animations_.clear();
}

const AnimatedSprite::KeyFrame & AnimatedSprite::find_key_frame(int animation, float timer) const
{
	const auto& key_frames = animations_.at(animation);
	timer = fmod(timer, animation_end_time(animation) + 1.0f);
	for (const auto& key_frame : key_frames) {
		if (timer <= key_frame.first)
			return key_frame;
	}
	return key_frames.back();
}
