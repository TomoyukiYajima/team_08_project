#ifndef ENEMY_ACTION_NUMBER_H_
#define ENEMY_ACTION_NUMBER_H_

enum class EnemyActionNumber {
	ACTION_IDEL		= 1 << 0,
	ACTION_CHASE	= 1 << 1,
	ACTION_ATTACK	= 1 << 2,
	ACTION_DAMAGE	= 1 << 3,
	ACTION_DEAD		= 1 << 4
};

#endif