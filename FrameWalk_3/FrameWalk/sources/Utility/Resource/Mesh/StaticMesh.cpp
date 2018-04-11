#include "StaticMesh.h"
#include <DxLib.h>

int StaticMesh::model_{ -1 };
Matrix StaticMesh::world_matrix_{ Matrix::Identity };
ModelAsset StaticMesh::asset_;

void StaticMesh::initialize()
{
	finalize();
}

void StaticMesh::finalize()
{
	asset_.clear();
}

bool StaticMesh::load(int id, const std::string file_name)
{
	return asset_.load(id, file_name);
}

void StaticMesh::erase(int id)
{
	asset_.erase(id);
	model_ = (model_ == id) ? -1 : model_;
}

void StaticMesh::bind(int id)
{
	model_ = asset_[id];
}

void StaticMesh::draw()
{
	MV1SetMatrix(model_, world_matrix_);
	MV1DrawModel(model_);
}

void StaticMesh::transform(const Matrix & world)
{
	world_matrix_ = world;
}
