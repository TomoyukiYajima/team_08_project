#include "ModelAnimation.h"
//#include "DxLib.h"
#include <cmath>
#include "../../../Math/Vector3.h"
#include "../../../Math/Matrix.h"

// コンストラクタ
ModelAnimation::ModelAnimation(int model, int motion, bool loop) :
	model_(model) {
	// モーションの変更
	change_motion(motion, loop);
}

// 更新
void ModelAnimation::update(float deltaTime) {
	// 補間中の処理
	if (prev_index_ != -1) {
		// アニメーションの補間
		const float amount = lerp_timer_ / LerpTime;
		// 行列を線形補間して補間している
		// あまりにもモーションが違いすぎると、モデルが変になる
		// 行列単位なので、複数個補間することも可能
		// 第三引数 : 補間具合 大きいほどそのモーションが強く出る
		MV1SetAttachAnimBlendRate(model_, prev_index_, 1.0f - amount);
		MV1SetAttachAnimBlendRate(model_, index_, amount);
		// 補間終了した時の処理
		if (lerp_timer_ >= LerpTime) {
			// 古いアニメーションの削除
			MV1DetachAnim(model_, prev_index_);
			prev_index_ = -1;
		}
		// 補間タイマを更新
		lerp_timer_ = std::fmin(lerp_timer_ + deltaTime, LerpTime);
	}

	// 再生
	MV1SetAttachAnimTime(model_, index_, motion_timer_);
	// アニメーションタイマの更新
	// 一秒 30f で終わるようにする
	motion_timer_ += 0.5f * deltaTime;
	// ループする場合は、float のあまりの時間を渡す
	if (is_loop_) motion_timer_ = std::fmod(motion_timer_, end_time());
	motion_timer_ = std::fmin(motion_timer_, end_time());
}

// モーションの変更
void ModelAnimation::change_motion(int motion, bool loop) {
	// 現在と同じモーションの場合は、何もしない
	if (motion_ == motion) return;
	// 補間中の前回のモーションを削除
	if (prev_index_ != -1) MV1DetachAnim(model_, prev_index_);

	// 前回のモーションを設定
	prev_motion_ = motion_;
	prev_motion_timer_ = motion_timer_;
	prev_index_ = index_;

	// モーションの更新
	motion_ = motion;
	// 古いアニメーションをデタッチ
	//if (index_ != -1) MV1DetachAnim(model_, index_);
	// 新しいアニメーションをアタッチ
	index_ = MV1AttachAnim(model_, motion);
	// モーション時間の変更
	motion_timer_ = 0.0f;
	// 補間タイマを初期化
	lerp_timer_ = 0.0f;
	// アニメーションの更新
	//MV1SetAttachAnimTime(model_, index_, motion_timer_);
	MV1SetAttachAnimTime(model_, index_, 0.0f);
	// ループフラグを設定
	is_loop_ = loop;
}

//ModelAnimation::ModelAnimation(const int id, const int number, const float speed) :
//	id_(id),
//	animeNum_(number),
//	attachNum_(0),
//	speed_(speed),
//	timer_(0.0f),
//	totalTimer_(0.0f),
//	isLoop_(true)
//{
//	// アニメーションのアタッチ
//	attachNum_ = MV1AttachAnim(id_, animeNum_, -1, FALSE);
//	//  MV1GetAnimNum(						int MHandle ) ;
//	// アタッチしたアニメーションの総再生時間を取得する
//	totalTimer_ = MV1GetAttachAnimTotalTime(id_, attachNum_);
//}
//
//void ModelAnimation::update(float deltaTime)
//{
//	//auto id = ResourceLoader::GetInstance().getModelID(id_);
//	timer_ = min(timer_ += speed_ * deltaTime / 6, totalTimer_);
//	// 総再生時間を超えた時の処理
//	if (timer_ >= totalTimer_) {
//		if (isLoop_) timer_ = 0.0f;
//		//else timer_ = totalTimer_;
//	}
//
//	// モデルの位置更新
//	//MV1SetPosition(id, Vector3::Vector3ToVECTOR(position_));
//	// アニメーションの再生
//	MV1SetAttachAnimTime(id_, attachNum_, timer_);
//}
//
//void ModelAnimation::draw(const Vector3 & position) const
//{
//	// モデルの位置更新
//	MV1SetPosition(id_, Vector3::Vector3ToVECTOR(position));
//	// モデルの描画
//	MV1DrawModel(id_);
//}
//
//void ModelAnimation::change(const int number, const bool isLoop, const float speed)
//{
//	// 同一のアニメーションなら変更しない
//	if (animeNum_ == number) return;
//	MV1DetachAnim(id_, attachNum_);
//	attachNum_ = MV1AttachAnim(id_, number);
//	animeNum_ = number;
//	speed_ = speed;
//	isLoop_ = isLoop;
//	timer_ = 0.0f;
//	totalTimer_ = MV1GetAttachAnimTotalTime(id_, attachNum_);
//}
//
//void ModelAnimation::changeSpeed(const float speed) { speed_ = speed; }
//
//float ModelAnimation::getAnimationTime() { return timer_; }
//
//bool ModelAnimation::isEndAnimation() { return timer_ >= totalTimer_; }
//
//void ModelAnimation::RotationYModel(const float degree)
//{
//	MV1SetRotationMatrix(
//		id_, 
//		Matrix::MatrixToMATRIX(Matrix::CreateRotationY(degree))
//		);
//}
