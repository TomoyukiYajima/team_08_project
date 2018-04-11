#include "Skydome.h"
#include <DxLib.h>

int SkyDome::handle_{ -1 };
//SkyDome::SkyDome(const SkyID id)
//{
//	//handle_ = ResourceLoader::GetInstance().getSkyID(id);
//}

void SkyDome::bind(const SkyID id)
{
	//handle_ = ResourceLoader::GetInstance().getSkyID(id);
}

void SkyDome::draw()
{
	//// カメラの位置にスカイドームを移動させる
	//auto camera = world_->findActor("Camera");
	//auto position = Vector3::Zero;
	//if (camera != nullptr) position = camera->getPosition();
	//MV1SetPosition(handle_, position);
	//MV1DrawModel(handle_);

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
	MV1SetWriteZBuffer(handle_, false);
	// モデルの表示
	MV1DrawModel(handle_);
	// 視野変換を元に戻す
	SetCameraViewMatrix(view_matirx);
	// ライティング処理を有効化する
	SetUseLighting(TRUE);
}
