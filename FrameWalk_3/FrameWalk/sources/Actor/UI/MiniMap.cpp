#include "MiniMap.h"
#include "../Base/Actor.h"
#include "../Base/ActorGroup.h"
#include "../Character/Enemy/Enemy.h"
#include "../../Math/Color.h"
#include "../../World/IWorld.h"
#include "../../Field/Field.h"
#include "../../Utility/Resource/Graphic/Graphics2D/Graphics2D.h"
#include "../../Utility/Resource/ResourceLoader/ResourceID.h"

MiniMap::MiniMap() : 
	world_(nullptr),
	position_(Vector2::Zero),
	scale_(1.0f)
{
	//positions_.clear();
	enemys_.clear();
}

MiniMap::MiniMap(IWorld* world, Vector2 position, float scale) :
	world_(world),
	position_(position),
	scale_(scale)
{
	//positions_.clear();
	enemys_.clear();
}

void MiniMap::update(float deltaTime)
{
	//positions_.clear();
	enemys_.clear();

	auto player = world_->findActor("Player");
	// 敵との距離の計算
	auto enemys = world_->findActors(ActorGroup::Enemy);
	for (auto i = enemys.begin(); i != enemys.end(); ++i) {
		/*auto pos = Vector2(
			player->getPosition().x - i->get()->getPosition().x,
			player->getPosition().z + i->get()->getPosition().z);
		positions_.push_back(pos * 8);*/
		enemys_.push_back(*i);
	}
	//GSvector2 playerPosition = GSvector2(
	//	player->getPosition().x, player->getPosition().z);
}

void MiniMap::draw() const
{
	// マップ本体
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(0.5f * 255));
	Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_RADAR, position_);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	auto size = Graphics2D::get_sprite_size((int)TextureID::GAMEPLAY_TEXTURE_RADAR);
	auto center = Vector2(size.x / 2, size.y / 2);
	// プレイヤーの位置
	SetDrawBright(255, 0, 0);
	Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_PT, position_ + center);
	SetDrawBright(255, 255, 255);

	// 敵の位置
	auto player = world_->findActor("Player");
	for (auto i = enemys_.begin(); i != enemys_.end(); ++i) {
		auto pos = Vector2(
			player->getPosition().x - i->get()->getPosition().x, 
			-(player->getPosition().z - i->get()->getPosition().z));
		auto drawPos = pos * scale_ + position_ + center;

		auto enemy = dynamic_cast<Enemy*>(i->get());
		// 色の変更
		auto color = Color(0, 1.0f, 0);
		if (enemy->getState() == Enemy::State::Damage) {
			color.r = 1.0f;
			color.g = 0.5f;
		}
		if (drawPos.x < position_.x || drawPos.x > position_.x + size.x) continue;
		else if (drawPos.y < position_.y || drawPos.y > position_.y + size.y) continue;
		SetDrawBright((int)(color.r * 255), (int)(color.g * 255), 0);
		Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_PT, drawPos);
		SetDrawBright(255, 255, 255);
	}

	// 壁
	auto fieldScale = world_->getField()->getFieldScale();
	auto scale = 1;
	// X
	auto playerPos = Vector2(
		player->getPosition().x - fieldScale.x,
		-(player->getPosition().z - fieldScale.z));
	auto wallPos = playerPos * scale_ + position_ + center;
	wallPos.y -= fieldScale.z * scale_ * 2;
	// 上下の描画
	for (int i = 0; i != 2; ++i) {
		for (int i = 0; i != (int)(fieldScale.x / scale) * 2 + 1; ++i) {
			if (wallPos.x >= position_.x && wallPos.x <= position_.x + size.x) {
				if (wallPos.y >= position_.y && wallPos.y <= position_.y + size.y) {
					SetDrawBright(0, 255, 200);
					Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_PT, wallPos);
					SetDrawBright(255, 255, 255);
				}
			}
			wallPos.x += scale * scale_;
		}
		// 下に変更
		wallPos = playerPos * scale_ + position_ + center;
	}
	// 左右の描画
	wallPos = playerPos * scale_ + position_ + center;
	for (int i = 0; i != 2; ++i) {
		for (int i = 0; i != (int)(fieldScale.z / scale) * 2 + 1; ++i) {
			if (wallPos.x >= position_.x && wallPos.x <= position_.x + size.x) {
				if (wallPos.y >= position_.y && wallPos.y <= position_.y + size.y) {
					SetDrawBright(0, 255, 200);
					Graphics2D::draw_sprite((int)TextureID::GAMEPLAY_TEXTURE_PT, wallPos);
					SetDrawBright(255, 255, 255);
				}
			}
			wallPos.y -= scale * scale_;
		}
		// 右に変更
		wallPos = playerPos * scale_ + position_ + center;
		wallPos.x += fieldScale.x * scale_ * 2;
	}
}
