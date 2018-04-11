#include "ModelAsset.h"
#include <DxLib.h>

ModelAsset::~ModelAsset()
{
	clear();
}

bool ModelAsset::load(int id, const std::string & file_name)
{
	erase(id);
	assets_[id] = MV1LoadModel(file_name.c_str());
	return true;
}

void ModelAsset::erase(int id)
{
	// assets_.count(id) > 0 ƒ‚ƒfƒ‹‚ª‚ ‚é‚©‚ğ’²‚×‚é
	if (assets_.count(id) > 0) {
		MV1DeleteModel(assets_[id]);
		assets_.erase(id);
	}
}

void ModelAsset::clear()
{
	for (const auto model : assets_) {
		// ƒnƒ“ƒhƒ‹‚Ìíœ
		MV1DeleteModel(model.second);
	}
	assets_.clear();
}

int ModelAsset::operator[](int id) const { return assets_.at(id); }
