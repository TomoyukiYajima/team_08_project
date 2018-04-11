#ifndef EVENT_MESSAGE_H_
#define EVENT_MESSAGE_H_

enum class EventMessage {
	CandleBroken,	// ロウソクが壊れた時のメッセージ
	EnemyDead,		// 敵を死亡させるメッセージ
	AddScore,		// 得点を加算
	AddEnemyCount,	// 敵のカウントの追加
	AddPlayerAP		// プレイヤーのAPを加算します
};

#endif

