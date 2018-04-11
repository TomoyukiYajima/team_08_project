#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

enum class ActorGroup {
	NULL_GROUP,			// 空のグループ
	Player,				// プレーヤ
	Enemy,				// 敵
	PlayerBullet,		// プレーヤ弾
	EnemyBullet,		// 敵弾
	Effect,				// エフェクト
	GimmickObject,		// ギミックオブジェクト
	BuilDing,			// 建物
};

#endif
