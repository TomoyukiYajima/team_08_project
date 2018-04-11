#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Base/Actor.h"

class Camera : public Actor {
public:
	// �R���X�g���N�^
	explicit Camera(IWorld* world);
private:
	// ������
	void initialize();
	// �X�V
	virtual void onUpdate(float deltaTime) override;
	// �`��
	virtual void onDraw() const override;
};


#endif
