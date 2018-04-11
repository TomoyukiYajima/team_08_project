#ifndef ISCENE_H_
#define ISCENE_H_

#include "DxLib.h"
#include "Scene.h"
#include "../../Utility/Input/InputManager.h"
#include <string>

class IScene {
public:
	//仮想デストラクタ
	virtual ~IScene() {}
	//初期化
	virtual void start() = 0;
	//更新
	virtual void update(float deltaTime) = 0;
	//描画
	virtual void draw() const = 0;
	//終了フラグ
	virtual bool isEnd() const = 0;
	//次のシーン
	virtual Scene next() const = 0;
	//終了
	virtual void end() = 0;
	// シーン名の取得
	std::string getName() { return name_; }
	// 次のシーン名の取得
	virtual std::string nextName() { return "next"; }
	// シーン名の設定
	void setName(std::string name) { name_ = name; }

public:
	bool isEnd_;		// 終了するか？
	//SceneDataKeeper* keeper_;
	std::string name_;	// シーン名
};

#endif