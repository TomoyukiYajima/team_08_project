#ifndef IWORLD_H_
#define IWORLD_H_

#include "../Actor/Base/ActorPtr.h"
#include "../Field/FieldPtr.h"
#include <string>
#include <forward_list>

enum class ActorGroup;
enum class EventMessage;

// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) = 0;
	// アクターの検索(forward_listを返します)
	virtual std::forward_list<ActorPtr>findActors(const ActorGroup group) = 0;
	// フィールド内に存在するアクターグループの数を取得します
	virtual int getActorCount(ActorGroup group) = 0;
	// フィールドの取得
	virtual FieldPtr getField() const = 0;
	// ゲームクリアかどうかを設定します
	virtual void setIsGameClear(bool isClear) = 0;
	// ゲームクリアかどうかを返します
	virtual bool isGameClear() = 0;
	// 強制的にゲームクリアをするかを設定します
	virtual void setIsGameClearEnd(bool isClearEnd) = 0;
	// 強制的にゲームクリアするかを返します
	virtual bool isGameClearEnd() = 0;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
};

#endif
