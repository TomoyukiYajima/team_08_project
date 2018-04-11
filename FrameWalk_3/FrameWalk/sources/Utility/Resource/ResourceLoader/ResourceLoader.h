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

	// ���f����ǂݍ��݂܂�
	void loadModel(const ModelID& id, const char* fileName);
	// �e�N�X�`����ǂݍ��݂܂�	
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
	// �t�B�[���h��ǂݍ��݂܂�
	void loadField(const FieldID& id, const char* fileName);
	// �X�J�C��ǂݍ��݂܂�
	void loadSky(const SkyID& id, const char* fileName);
	// SE��ǂݍ��݂܂�
	void loadSE(
		const SoundID& id, const char* fileName, 
		const bool isStopSound = false
		);
	// BGM��ǂݍ��݂܂�
	void loadBGM(const SoundID& id, const char* fileName);
	// �t�B�[���hID���擾���܂�
	int getFieldID(const FieldID& id);
	// �X�J�CID���擾���܂�
	int getSkyID(const SkyID& id);

private:
	std::unordered_map<FieldID, int> fields_;
	std::unordered_map<SkyID, int> skies_;
};

#endif