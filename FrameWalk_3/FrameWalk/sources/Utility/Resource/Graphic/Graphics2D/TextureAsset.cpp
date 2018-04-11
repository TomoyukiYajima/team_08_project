#include "TextureAsset.h"
#include <DxLib.h>

TextureAsset::~TextureAsset()
{
	clear();
}

bool TextureAsset::load(int id, const std::string & file_name)
{
	erase(id);
	assets_[id] = LoadGraph(file_name.c_str());
	return assets_[id] != -1;
}

void TextureAsset::erase(int id)
{
	if (assets_.count(id) > 0) {
		DeleteGraph(assets_[id]);
		assets_.erase(id);
	}
}

void TextureAsset::clear()
{
	// 全てのアセットが削除されていなかったら、削除する
	for (const auto model : assets_) {
		DeleteGraph(model.second);
	}
	assets_.clear();
}

int TextureAsset::operator[](int id) const
{
	return assets_.at(id);
}
