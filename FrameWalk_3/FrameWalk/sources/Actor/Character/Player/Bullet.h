#ifndef BULLET_H_
#define BULLET_H_

#include "../../Base/Actor.h"

// 弾クラス
class Bullet : public Actor {
public:
	// コンストラクタ
	Bullet(IWorld* world, const Vector3& position);
	// 更新
	virtual void onUpdate(float deltaTime) override;
	virtual void onCollide(Actor&) override;
	//virtual void onDraw() const override;

private:
	// 消去タイム
	float deleteTime_;
	// 移動量
	//Vector3 velocity_;
};

#endif

