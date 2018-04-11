#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../Base/Actor.h"
#include "../../Base/EventMessage.h"

class IWorld;

// 敵
class Enemy : public Actor {
public:
	// モーション番号クラス
	enum {
		ENEMY_MOTION_IDEL = 9,
		ENEMY_MOTION_WALK = 1,
		ENEMY_MOTION_DAMAGE = 14,
		ENEMY_MOTION_DAMAGE_NOW = 15
	};

public:
	// 状態クラス
	enum class State {
		Idel,
		Move,
		LogOut,
		Damage
	};

public:
	Enemy(IWorld* world, const Vector3& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor&) override;
	virtual void onMessage(EventMessage event, void* param) override;

private:
	// 状態の更新
	void updateState(float deltaTime);
	// 状態の変更
	void changeState(State state, const int motion, const bool isLoop = true);
	// 待機
	void idel(float deltaTime, bool isLogOut);
	// 行動
	void move(float deltaTime);
	// ダメージ中
	void damage(float deltaTime);
	// 敵の点滅
	void flashEnemy(const float minAlpha, const float maxAlpha, float deltaTime);

public:
	// 状態を返します
	State getState();

private:
	// 待機時間
	float idelTime_;
	// 初期待機時間
	float initIdelTime_;

private:
	// 状態
	State state_;
	// 状態タイマ
	float stateTimer_;
	int motion_;
	float motionTimer_;

private:
	// 点滅間隔
	int flashInterval_;
	// 復帰時間(未使用)
	float comebackTime_;
	// 点滅時間
	float flashTime_;
	float alpha_;
};

#endif
