#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

class MathHelper {
public:
	// �΂̒l
	static const float Pi;
	// 3.14159265359f

	// �l���w�肳�ꂽ�͈͓��ɐ������܂�
	static float Clamp(float value, float min, float max);
	// 2�̒l�̍��̐�Βl���v�Z���܂�
	static float Distance(float n1, float n2);
	// 2�̒l�̊Ԃ���`��Ԃ��܂�
	static float Lerp(float value1, float value2, float amount);
	// ���W�A����x�ɕϊ����܂�
	static float ToDegrees(float radians);
	// �x�����W�A���ɕϊ����܂�
	static float ToRadius(float degree);
	// �������v�Z���܂�
	static float Sin(float degree);
	// �]�����v�Z���܂�
	static float Cos(float degree);
	// ���ڂ��v�Z���܂�
	static float Tan(float degree);
	// �t�������v�Z���܂�
	static float ASin(float s);
	// �t�]�����v�Z���܂�
	static float ACos(float c);
	// �t���ڂ��v�Z���܂�
	static float ATan(float y, float x);
	// �ϐ��̕������󂯎��܂�
	static int Sign(float value);
};

#endif
