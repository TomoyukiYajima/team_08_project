#ifndef GAMEDEVICE_H_
#define GAMEDEVICE_H_

#include "DxLib.h"

class GameDevice {
public:
	GameDevice(
		int width, int height, 
		float rate, int windowMode,
		int colorBitDepth = 32);
	~GameDevice(){}

	//バッファをフリップ
	void flip();
private:
	// コピー禁止
	GameDevice(const GameDevice& other) = delete;
	GameDevice& operator = (const GameDevice& other) = delete;
};

#endif