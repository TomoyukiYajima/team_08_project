#ifndef RANDOM_H_
#define RANDOM_H_

// 乱数クラス
class Random {
public:
	// 乱数生成器の初期化
	static void randomize();
	// 乱数生成器の初期化
	static void randomize(unsigned int seed);
	// int型の乱数を求める
	static int rand(int l, int h);
	// float型の乱数を求める
	static float rand(float l, float h);
	// 乱数のシード値を取得
	static unsigned int seed();
};

#endif