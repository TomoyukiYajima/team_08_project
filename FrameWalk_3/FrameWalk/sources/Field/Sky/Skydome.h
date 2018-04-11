#ifndef SKY_DOME_H_
#define SKY_DOME_H_

#include "../../Utility/Resource/ResourceLoader/ResourceLoader.h"

class SkyDome {
public:
	//SkyDome(const SkyID id);
	// メッシュのバインド
	static void bind(const SkyID id);
	static void draw();

private:
	static int handle_;
	//SkyID id_;
};

#endif