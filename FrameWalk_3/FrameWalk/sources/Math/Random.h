#ifndef RANDOM_H_
#define RANDOM_H_

// �����N���X
class Random {
public:
	// ����������̏�����
	static void randomize();
	// ����������̏�����
	static void randomize(unsigned int seed);
	// int�^�̗��������߂�
	static int rand(int l, int h);
	// float�^�̗��������߂�
	static float rand(float l, float h);
	// �����̃V�[�h�l���擾
	static unsigned int seed();
};

#endif