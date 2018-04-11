#ifndef MODEL_ASSET_H_
#define MODEL_ASSET_H_

#include <unordered_map>
#include <string>

class ModelAsset {
public:
	// �R���X�g���N�^
	ModelAsset() = default;
	// �f�X�g���N�^
	~ModelAsset();
	// �ǂݍ���
	bool load(int id, const std::string& file_name);
	// �폜
	void erase(int id);
	// ����
	void clear();
	// �n���h���̎擾
	int operator [](int id) const;
	// �R�s�[�֎~
	ModelAsset(const ModelAsset& other) = delete;
	ModelAsset operator = (const ModelAsset& other) = delete;

private:
	// ���f���f�[�^�}�b�v
	std::unordered_map<int, int> assets_;
};

#endif