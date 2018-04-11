#include "Camera.h"
#include "../../World/IWorld.h"

// コンストラクタ
Camera::Camera(IWorld* world) :
	Actor(world, "Camera", Vector3(0.0f, 0.0f, 0.0f)) {
}

// 初期化
void Camera::initialize()
{
	// プレーヤを検索
	auto player = world_->findActor("Player");
	// プレーヤがいない
	if (player == nullptr) return;
	// プレーヤの座標を取得
	position_ = player->getPosition();
	// プレーヤの回転（向き）を取得
	rotate_ = player->getRotate();

	// カメラの位置変更
	SetCameraPositionAndTarget_UpVecY(
		position_ - Vector3(0.0f, 2.0f, 0.0f),
		position_);
	SetCameraViewMatrix(rotate_);
}

// 更新
void Camera::onUpdate(float deltaTime) {
	(void)deltaTime;
	//// プレーヤを検索
	//auto player = world_->findActor("Player");
	//// プレーヤがいない
	//if (player == nullptr) return;

	//// プレーヤの座標を取得
	//position_ = player->getPosition() + GSvector3(0.0f, 2.0f, 0.0f);
	//// プレーヤの回転（向き）を取得
	//rotate_ = player->getRotate();

	//// カメラの移動
	//// プレイヤーを軸に回転する
	//if (gsGetKeyState(GKEY_D) == GS_TRUE) {

	//}
	//else if (gsGetKeyState(GKEY_A) == GS_TRUE) {

	//}
}

// 描画
void Camera::onDraw() const 
{
	/*glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(getPose().convertViewRH());*/
}
