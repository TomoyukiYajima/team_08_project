#ifndef GAMEPLAYSCENE_H_
#define GAMEPLAYSCENE_H_

#include "../Base/IScene.h"
#include "../../World/World.h"
#include "../../Actor/UI/Score.h"
#include "../../Actor/UI/GamePlayTimer.h"
#include "../../Actor/UI/MiniMap.h"
#include "../../Actor/UI/Result.h"

class GamePlayScene : public IScene {
public:
	// コンストラクタ
	GamePlayScene();
	// デストラクタ
	virtual ~GamePlayScene();
	// 開始
	virtual void start() override;
	// 更新
	virtual void update(float deltaTime) override;
	// 描画
	virtual void draw() const override;
	// 終了しているか？
	virtual bool isEnd() const override;
	// 次のシーンを返す
	virtual Scene next() const override;
	// 終了
	virtual void end() override;
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	// 敵生成関数
	void enemyCreate();
	// 条件
	int rankCount();

private:
	using WorldPtr = std::shared_ptr<World>;
	WorldPtr	world_;				// ワールド
	// スコア
	Score		score_;
	// ゲームタイマ
	GamePlayTimer gameTimer_;
	// リザルト
	Result result_;
	// ミニマップ
	MiniMap miniMap_;
	// 敵生成カウント
	int	enemyCreateCount_;
	bool isGameOver_;
};

#endif