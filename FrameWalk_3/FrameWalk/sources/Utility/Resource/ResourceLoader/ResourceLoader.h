#ifndef RESOURCE_LOADER_H_
#define RESOURCE_LOADER_H_

#include "DxLib.h"
#include "ResourceID.h"
#include "../../../Math/Vector2.h"
#include <unordered_map>

class ResourceLoader {
private:
	ResourceLoader();
	~ResourceLoader();

public:
	static ResourceLoader& GetInstance();

	// モデルを読み込みます
	void loadModel(const ModelID& id, const char* fileName);
	// テクスチャを読み込みます	
	void loadTexture(const TextureID& id, const char* fileName);
	/*void loadAnimation(const AnimationID& id, const char* fileName, 
		const Vector2& size, const int& row, const int& column, 
		const int& surplus = 0
		);
	void loadAnimation(
		const AnimationID& id, const char* fileName, 
		const int& size, const int& row, const int& column, 
		const int& surplus = 0
		);*/
	// フィールドを読み込みます
	void loadField(const FieldID& id, const char* fileName);
	// スカイを読み込みます
	void loadSky(const SkyID& id, const char* fileName);
	// SEを読み込みます
	void loadSE(
		const SoundID& id, const char* fileName, 
		const bool isStopSound = false
		);
	// BGMを読み込みます
	void loadBGM(const SoundID& id, const char* fileName);
	// フィールドIDを取得します
	int getFieldID(const FieldID& id);
	// スカイIDを取得します
	int getSkyID(const SkyID& id);

private:
	std::unordered_map<FieldID, int> fields_;
	std::unordered_map<SkyID, int> skies_;
};

#endif