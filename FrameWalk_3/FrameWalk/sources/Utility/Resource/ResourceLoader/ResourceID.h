#ifndef RESOURCE_ID_H_
#define RESOURCE_ID_H_

enum class ModelID {
	PLAYER_MODEL = 0,
	ENEMY_MODEL = 1
};

enum class ModelAnimationID {
	SAMPLE_MODEL_ANIMATION_STAND = 0
};

enum class FieldID {
	KOUTEI_FIELD = 0
};

enum class SkyID {
	KOUTEI_SKYBOX = 0
};

enum class TextureID {
	SAMPLE_TEX = 111,
	TEXRUER_EFFECT = 0,
	TEXRUER_SCORE = 1,
	TITLE_TEXTURE_TITLE = 2,
	TITLE_TEXTURE_KENDO = 3,
	TITLE_TEXTURE_KARATE = 4,
	TITLE_TEXTURE_OSU = 5,
	GAMEPLAY_TEXTURE_TEXTS = 6,
	GAMEPLAY_TEXTURE_PT = 7,
	GAMEPLAY_TEXTURE_RADAR = 8,
	RESULT_TEXTURE_BACKGROUND = 9,
	RESULT_TEXTURE_RESULT_1 = 10,
	RESULT_TEXTURE_RESULT_2 = 11,
	RESULT_SCREENSHOT = 12
};

enum class TextureAnimationID {

};

enum class SoundID {
	BGM_TITLE = 0,
	BGM_STAGE1 = 1,
	BGM_ED = 2,
	BGM_TIMEEND = 3,
	SE_ATTACK1 = 20,
	SE_ATTACK2 = 21,
	SE_DAMAGE = 22,
	SE_SELECT = 23,
	SAMPLE_SE = 114,
	SAMPLE_BGM = 514
};

#endif