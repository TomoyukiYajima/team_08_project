#include "Skybox.h"
#include <DxLib.h>

// バインド中のモデル
int Skybox::model_{ -1 };
// モデルアセット
ModelAsset Skybox::asset_;

void Skybox::initialize()
{
	finalize();
}

void Skybox::finalize()
{
	asset_.clear();
}

bool Skybox::load(int id, const std::string file_name)
{
	return asset_.load(id, file_name);
}

void Skybox::erase(int id)
{
	asset_.erase(id);
	model_ = (model_ == id) ? -1 : model_;
}

void Skybox::bind(int id)
{
	model_ = asset_[id];
}

void Skybox::draw()
{
	// 視野変換行列の取得
	MATRIX view_matirx = GetCameraViewMatrix();
	// 視野変換行列の平行移動量をクリア
	MATRIX skybox_matrix = view_matirx;
	for (int i = 0; i != 3; ++i) {
		skybox_matrix.m[3][i] = 0.0f;
	}
	// 視野変換行列の設定
	SetCameraViewMatrix(skybox_matrix);
	// ライティング処理を無効にする
	SetUseLighting(FALSE);
	// Zバッファに書き込みを行わない
	MV1SetWriteZBuffer(model_, false);
	// モデルの表示
	MV1DrawModel(model_);
	// 視野変換を元に戻す
	SetCameraViewMatrix(view_matirx);
	// ライティング処理を有効化する
	SetUseLighting(TRUE);
}
