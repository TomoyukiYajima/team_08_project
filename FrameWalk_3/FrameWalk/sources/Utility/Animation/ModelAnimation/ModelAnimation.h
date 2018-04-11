#ifndef MODEL_ANIMATION_H_
#define MODEL_ANIMATION_H_

#include "DxLib.h"

struct Vector3;

class ModelAnimation {
public:
	// コンストラクタ
	ModelAnimation(int model, int motion, bool loop = false);
	// 更新
	void update(float deltaTime);
	// モーションの変更
	void change_motion(int motion, bool loop = false);
	// 現在再生中のモーション
	int motion() const { return motion_; }
	// ボーンを返す
	int bone_count() const { return MV1GetFrameNum(model_); }
	// 終了時間を返す
	float end_time() const { return MV1GetAttachAnimTotalTime(model_, index_); }

	//// アニメーションの変更をします
	//void change(
	//	const int number, const bool isLoop = true, const float speed = 1.0f
	//	);
	//// 再生速度の変更します
	//void changeSpeed(const float speed);
	//// アニメーションの現在の時間を取得します
	//float getAnimationTime();
	//// アニメーションが終了したかを返します
	//bool isEndAnimation();

	//void RotationYModel(const float degree);

private:
	// モデルハンドラ
	int model_{ -1 };
	// 再生中のアニメーション
	int motion_{ -1 };
	// アタッチ中のインデックス
	int index_{ -1 };
	// 再生中のアニメーションタイマ
	float motion_timer_{ 0.0f };

	// 前のモデルハンドラ
	int prev_model_{ -1 };
	// 前の再生中のアニメーション
	int prev_motion_{ -1 };
	// 前のアタッチ中のインデックス
	int prev_index_{ -1 };
	// 前の再生中のアニメーションタイマ
	float prev_motion_timer_{ 0.0f };

	// 補間タイマ
	float lerp_timer_{ 0.0f };
	// ループフラグ
	bool is_loop_{ false };
	// 補間タイマ
	const float LerpTime{ 10.0f };
};

#endif