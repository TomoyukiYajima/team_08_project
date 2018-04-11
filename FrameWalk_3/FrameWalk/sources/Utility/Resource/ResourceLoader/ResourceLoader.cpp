#include "ResourceLoader.h"

#include "../Mesh/SkeletalMesh.h"
#include "../Graphic/Graphics2D/Graphics2D.h"
#include "../Sound/Sound.h"

ResourceLoader::ResourceLoader() {
	Graphics2D::initialize();
	SkeletalMesh::initialize();
	Sound::initialize();
}

ResourceLoader::~ResourceLoader()
{
	Graphics2D::finalize();
	SkeletalMesh::finalize();
	Sound::finalize();
}

ResourceLoader & ResourceLoader::GetInstance()
{
	static ResourceLoader instance;
	return instance;
}

void ResourceLoader::loadModel(const ModelID & id, const char * fileName)
{
	SkeletalMesh::load((int)id, fileName);
}

void ResourceLoader::loadTexture(const TextureID & id, const char * fileName)
{
	Graphics2D::load_sprite((int)id, fileName);
}

void ResourceLoader::loadField(const FieldID & id, const char * fileName)
{
	int handle = MV1LoadModel(fileName);
	// 読み込めなかったら例外処理
	if (handle == -1) throw std::string("指定したモデルファイルは存在しません");

	fields_[id] = handle;
}

void ResourceLoader::loadSky(const SkyID & id, const char * fileName)
{
	int handle = MV1LoadModel(fileName);
	// 読み込めなかったら例外処理
	if (handle == -1) throw std::string("指定したモデルファイルは存在しません");

	skies_[id] = handle;
}

void ResourceLoader::loadSE(
	const SoundID & id, const char * fileName, 
	const bool isStopSound)
{
	Sound::load_se((int)id, fileName);
}

void ResourceLoader::loadBGM(const SoundID & id, const char * fileName)
{
	Sound::load_bgm((int)id, fileName);
}

int ResourceLoader::getFieldID(const FieldID & id) { return fields_[id]; }

int ResourceLoader::getSkyID(const SkyID & id) { return skies_[id]; }


