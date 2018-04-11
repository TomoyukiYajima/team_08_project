#include "SkeletalMesh.h"
#include <DxLib.h>

// バインド中のモデル
int SkeletalMesh::model_{ -1 };
// ボーンのローカル変換行列
Matrix SkeletalMesh::local_matrices_[SkeletalMesh::BoneMax];
// ボーンのワールド変換行列
Matrix SkeletalMesh::world_matrices_[SkeletalMesh::BoneMax];
// モデルアセット
ModelAsset SkeletalMesh::asset_;

void SkeletalMesh::initialize()
{
	finalize();
}

void SkeletalMesh::finalize()
{
	asset_.clear();
}

bool SkeletalMesh::load(int id, const std::string file_name)
{
	return asset_.load(id, file_name);
}

void SkeletalMesh::erase(int id)
{
	asset_.erase(id);
	model_ = (model_ == id) ? -1 : model_;
}

void SkeletalMesh::bind(int id)
{
	model_ = asset_[id];
}

void SkeletalMesh::bind_animation(int motion, float time)
{
	const auto index = MV1AttachAnim(model_, motion);
	MV1SetAttachAnimTime(model_, index, time);

	for (int i = 0; i != MV1GetFrameNum(model_); ++i) {
		// フラグのリセット
		MV1ResetFrameUserLocalMatrix(model_, i);
		// MV1GetFrameLocalMatrix
		// 一回だけ呼ぶだけで、フラグが立つ
		// フラグが立つと、再計算されない
		local_matrices_[i] = MV1GetFrameLocalMatrix(model_, i);
	}
	MV1DetachAnim(model_, index);
}

void SkeletalMesh::bind_animation(int prev_motion, float prev_time, int motion, float time, float amount)
{
	const auto prev_index = MV1AttachAnim(model_, prev_motion);
	const auto now_index = MV1AttachAnim(model_, motion);
	MV1SetAttachAnimBlendRate(model_, prev_index, 1.0f - amount);
	MV1SetAttachAnimBlendRate(model_, now_index, amount);
	MV1SetAttachAnimTime(model_, prev_index, time);
	MV1SetAttachAnimTime(model_, now_index, time);

	for (int i = 0; i != MV1GetFrameNum(model_); ++i) {
		MV1ResetFrameUserLocalMatrix(model_, i);
		local_matrices_[i] = MV1GetFrameLocalMatrix(model_, i);
	}

	MV1DetachAnim(model_, prev_index);
	MV1DetachAnim(model_, now_index);
}

void SkeletalMesh::transform(const Matrix & world)
{
	// ローカル変換行列を設定
	for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
		MV1SetFrameUserLocalMatrix(model_, i, local_matrices_[i]);
	}
	// ワールド変換行列を設定
	MV1SetMatrix(model_, world);
	// ワールド変換行列を取得
	for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
		// ボーンのワールド変換行列
		// ボーンの位置が知りたいときはこれを使う
		world_matrices_[i] = MV1GetFrameLocalWorldMatrix(model_, i);
	}
}

void SkeletalMesh::draw()
{
	for (int i = 0; i != MV1GetFrameNum(model_); ++i) {
		MV1ResetFrameUserLocalMatrix(model_, i);
		MV1SetFrameUserLocalWorldMatrix(model_, i, world_matrices_[i]);
	}
	MV1DrawModel(model_);
}

void SkeletalMesh::draw(float alpha)
{
	MV1SetOpacityRate(model_, alpha);
	draw();
}

void SkeletalMesh::get_local_matrices(Matrix local_matrices[])
{
	for (int i = 0; i != MV1GetFrameNum(model_); ++i) {
		local_matrices[i] = local_matrices_[i];
	}
}

void SkeletalMesh::set_local_matrices(const Matrix local_matrices[])
{
	for (int i = 0; i != MV1GetFrameNum(model_); ++i) {
		local_matrices_[i] = local_matrices[i];
	}
}

void SkeletalMesh::get_world_matrices(Matrix world_matrices[])
{
	for (int i = 0; i != MV1GetFrameNum(model_); ++i) {
		world_matrices[i] = world_matrices_[i];
	}
}

void SkeletalMesh::set_world_matrices(const Matrix world_matrices[])
{
	for (int i = 0; i != MV1GetFrameNum(model_); ++i) {
		world_matrices_[i] = world_matrices[i];
	}
}

int SkeletalMesh::bone_count()
{
	return MV1GetFrameNum(model_ );
}

float SkeletalMesh::end_time(int motion)
{
	return MV1GetAnimTotalTime(model_, motion);
}
