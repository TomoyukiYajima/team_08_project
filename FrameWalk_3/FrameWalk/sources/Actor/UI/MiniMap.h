#ifndef MINIMAP_H_
#define MINIMAP_H_

#include "../Base/ActorPtr.h"
#include "../../Math/Vector2.h"
#include <vector>

class IWorld;

class MiniMap {
public:
	MiniMap();
	MiniMap(IWorld* world, Vector2 position, float scale);
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	//// �G�l�~�[�R���e�i�ɒǉ�
	//void addEnemy(ActorPtr enemy);
	// �v���C���[�̈ʒu�擾

private:
	// ���[���h�|�C���^
	IWorld* world_;
	// �ʒu
	Vector2 position_;
	float scale_;
	// �G�l�~�[�̈ʒu�R���e�i
	typedef std::vector<ActorPtr> EnemyContainer;
	EnemyContainer enemys_;
	//// �G�l�~�[�R���e�i
	//typedef std::vector<ActorPtr> EnemyContainer;
	//EnemyContainer mEnemyContainer;
};

#endif
