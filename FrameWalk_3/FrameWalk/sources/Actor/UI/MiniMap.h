#ifndef MINIMAP_H_
#define MINIMAP_H_

#include "../Base/ActorPtr.h"
#include "../../Math/Vector2.h"
#include <vector>

class IWorld;

class MiniMap {
public:
	MiniMap();
	MiniMap(IWorld* world, Vector2 position, float scale);
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	//// エネミーコンテナに追加
	//void addEnemy(ActorPtr enemy);
	// プレイヤーの位置取得

private:
	// ワールドポインタ
	IWorld* world_;
	// 位置
	Vector2 position_;
	float scale_;
	// エネミーの位置コンテナ
	typedef std::vector<ActorPtr> EnemyContainer;
	EnemyContainer enemys_;
	//// エネミーコンテナ
	//typedef std::vector<ActorPtr> EnemyContainer;
	//EnemyContainer mEnemyContainer;
};

#endif
