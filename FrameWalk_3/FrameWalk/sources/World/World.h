#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>
#include <forward_list>

enum class EventMessage;

class World : public IWorld {
public:
	// コンストラクタ
	World();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	// フィールドの追加
	void addField(const FieldPtr& field);
	// カメラの追加
	void addCamera(const ActorPtr& camera);
	// ライトの追加
	void addLight(const ActorPtr& light);

	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) override;
	// アクターの検索(forward_listを返します)
	virtual std::forward_list<ActorPtr>findActors(const ActorGroup group) override;
	// フィールド内に存在するアクターグループの数を取得します
	virtual int getActorCount(ActorGroup group) override;
	// フィールドの取得
	virtual FieldPtr getField() const override;
	// ゲームクリアかどうかを設定します
	virtual void setIsGameClear(bool isClear) override;
	// ゲームクリアかどうかを返します
	virtual bool isGameClear() override;
	// 強制的にゲームクリアをするかを設定します
	virtual void setIsGameClearEnd(bool isClearEnd) override;
	// 強制的にゲームクリアするかを返します
	virtual bool isGameClearEnd() override;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// イベントリスナーの追加
	void addEventMessageListener(
		std::function<void(EventMessage, void*)> listener);

	// コピー禁止
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	// アクターマネージャー
	ActorManager	actors_;
	// ライト
	ActorPtr		light_;
	// カメラ
	ActorPtr		camera_;
	// フィールド
	FieldPtr		field_;
	// イベントリスナー
	std::function<void(EventMessage, void*)> listener_;

private:
	bool isClear_;		// ゲームクリアするか
	bool isClearEnd_;	// ゲームクリアで強制終了するか
};

#endif

