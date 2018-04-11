#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "../Base/IScene.h"
#include "../../World/World.h"

class TitleScene : public IScene {
public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	virtual ~TitleScene();
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

private:
	// ボタンの透明度タイマ
	float alphaTimer_;
	// 剣道画像のX座標
	float kendoPositionX_;
	// 空手画像のX座標
	float karatePositionX_;
	// キャラクター画像のY座標
	float characterTexturePositionY_;
	// 画像のX座標加算数値(デルタタイムをかける)
	float textureMoveSpeed_;
	// ボタンの透明度
	float buttonAlpha_;
};

#endif