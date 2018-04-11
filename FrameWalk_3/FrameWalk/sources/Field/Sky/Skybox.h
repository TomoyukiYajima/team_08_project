#ifndef SKY_BOX_H_
#define SKY_BOX_H_

#include "../../Utility/Resource/Mesh/ModelAsset.h"
#include <string>

// スカイボックスクラス
class Skybox {
	// 初期化
	static void initialize();
	// 終了処理
	static void finalize();
	// 読み込み
	static bool load(int id, const std::string file_name);
	// 削除
	static void erase(int id);
	// メッシュのバインド
	static void bind(int id);
	// 描画
	static void draw();

private:
	// バインド中のモデル
	static int model_;
	// モデルアセット
	static ModelAsset asset_;
};

#endif