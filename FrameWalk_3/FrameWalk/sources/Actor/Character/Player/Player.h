#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Base/Actor.h"

class IWorld;

class Player : public Actor {
private:
	// 状態クラス
	enum class State {
		Idel,
		Move,
		Attack,
		Damage,
		ComeBack,
		Dead,
		ResPorn,
	};
	// モーション番号
	enum {
		MOTION_IDEL = 0,
		MOTION_WALK = 1,
		MOTION_ATTACK = 17,
		MOTION_DAMAGE = 14,
		MOTION_DAMAGENOW = 15,
		MOTION_COMEBACK = 16,
		MOTION_DEAD = 20,
		MOTION_RESPORN = 21
	};

public:
	Player(IWorld* world, const Vector3& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor&) override;
	virtual void onMessage(EventMessage event, void* param) override;

// 状態関連
private:
	// 状態の更新
	void updateState(float deltaTime);
	// 状態の変更
	void changeState(State state, const int motion, const bool isLoop = true);
	// 状態の更新
	void move(float deltaTime);
	// 攻撃中
	void attack(float deltaTime);
	// ダメージ中
	void damage(float deltaTime);
	// 復帰中
	void comeback(float deltaTime);

private:
	State state_;				// 状態
	float stateTimer_;			// 状態タイマ
	int motion_;
	float motionTimer_;
};

#endif