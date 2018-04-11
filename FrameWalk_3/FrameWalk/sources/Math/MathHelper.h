#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

class MathHelper {
public:
	// πの値
	static const float Pi;
	// 3.14159265359f

	// 値を指定された範囲内に制限します
	static float Clamp(float value, float min, float max);
	// 2つの値の差の絶対値を計算します
	static float Distance(float n1, float n2);
	// 2つの値の間を線形補間します
	static float Lerp(float value1, float value2, float amount);
	// ラジアンを度に変換します
	static float ToDegrees(float radians);
	// 度をラジアンに変換します
	static float ToRadius(float degree);
	// 正弦を計算します
	static float Sin(float degree);
	// 余弦を計算します
	static float Cos(float degree);
	// 正接を計算します
	static float Tan(float degree);
	// 逆正弦を計算します
	static float ASin(float s);
	// 逆余弦を計算します
	static float ACos(float c);
	// 逆正接を計算します
	static float ATan(float y, float x);
	// 変数の符号を受け取ります
	static int Sign(float value);
};

#endif
