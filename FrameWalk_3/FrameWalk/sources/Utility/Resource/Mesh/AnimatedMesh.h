#ifndef ANIMATED_MESH_H_
#define ANIMATED_MESH_H_

#include "../../../Math/Matrix.h"
#include "../../Animation/ModelAnimation/ModelAnimation.h"

// アニメーション付きメッシュクラス
class AnimatedMesh {
public:
	// コンストラクタ
	AnimatedMesh(int model, int motion = 0, bool loop = false);
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// 描画(透明度付き)
	void draw(float alpha) const;
	// 姿勢行列の設定
	void transform(const Matrix& matrix);
	// モーションの変更
	void change_motion(int motion, bool loop = false);
	// ボーンの変換行列を取得
	Matrix bone_matrix(int bone_no) const { return MV1GetFrameLocalWorldMatrix(model_, bone_no); }
	// 終了時間を返す
	float motion_end_time()const { return animation_.end_time(); }

private:
	// メッシュ
	int model_;
	// アニメーション
	ModelAnimation animation_;
};

#endif