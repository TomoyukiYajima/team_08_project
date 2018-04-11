#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include "../ResourceLoader/ResourceLoader.h"
#include <list>

class SoundPlayer {
private:
	SoundPlayer();
	~SoundPlayer();

public:
	static SoundPlayer& GetInstance();
	// サウンドの追加
	void addSound(const SoundID & id, const int handle, const bool isStopSound);
	// 一時停止させるサウンドか
	/*void addSound(
	const SoundID& id, const char* fileName,
	const bool isStopSound = false);*/
	// サウンドの再生
	void playSound(const SoundID id);
	// サウンドの再生(ループ)
	void playLoopSound(const SoundID id);
	// サウンドの停止
	void stopSound(const SoundID id);
	// 全てのサウンドの停止
	void stopAllSound();
	// サウンドの一時停止を行います
	void poseStopSound();
	// 一時停止したサウンドを再生します
	void poseRestartSound();
	// サウンドIDを取得します
	int getSoundID(const SoundID& id);

private:
	// サウンドマップ
	std::unordered_map<SoundID, int> sounds_;
	// 停止サウンドハンドルコンテナ
	typedef std::list<int> StopSoundContainer;
	StopSoundContainer stopSoundHandles_;
	// 再生サウンドハンドルコンテナ
	typedef std::list<int> PlaySoundContainer;
	PlaySoundContainer playSoundHandles_;
};

#endif