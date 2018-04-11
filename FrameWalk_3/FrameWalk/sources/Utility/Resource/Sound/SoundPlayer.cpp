#include "SoundPlayer.h"
#include "DxLib.h"

SoundPlayer::SoundPlayer() {
	sounds_.clear();
	stopSoundHandles_.clear();
	playSoundHandles_.clear();
}

SoundPlayer::~SoundPlayer() {
	sounds_.clear();
	stopSoundHandles_.clear();
	playSoundHandles_.clear();
}

SoundPlayer & SoundPlayer::GetInstance()
{
	static SoundPlayer instance;
	return instance;
}

//void SoundPlayer::addSound(const SoundID & id, const char * fileName, const bool isStopSound)
//{
//}

void SoundPlayer::addSound(const SoundID & id, const int handle, const bool isStopSound)
{
	sounds_[id] = handle;
	if (isStopSound) stopSoundHandles_.push_back(handle);
}

void SoundPlayer::playSound(const SoundID id)
{
	PlaySoundMem(getSoundID(id), DX_PLAYTYPE_BACK);
}

void SoundPlayer::playLoopSound(const SoundID id)
{
	PlaySoundMem(getSoundID(id), DX_PLAYTYPE_LOOP);
}

void SoundPlayer::stopSound(const SoundID id)
{
	StopSoundMem(getSoundID(id));
}

void SoundPlayer::stopAllSound()
{
	for (auto i = sounds_.begin(); i != sounds_.end(); i++) {
		auto sound = *i;
		if (CheckSoundMem(sound.second) == 1)
			StopSoundMem(sound.second);
	}
}

void SoundPlayer::poseStopSound()
{
	// 再生リストに入っていた場合は返す
	if (playSoundHandles_.size() != 0) return;
	// 再生していたサウンドを止める。再生リストに追加する
	for (auto i = stopSoundHandles_.begin(); i != stopSoundHandles_.end(); i++) {
		if (CheckSoundMem(*i) == 1) {
			StopSoundMem(*i);
			playSoundHandles_.push_back(*i);
		}
	}
}

void SoundPlayer::poseRestartSound()
{
	// サイズが空ならば返す
	if (playSoundHandles_.size() == 0) return;
	for (auto i = playSoundHandles_.begin(); i != playSoundHandles_.end(); i++) {
		// 格納したSEを再生する
		if (CheckSoundMem(*i) == 0)
			PlaySoundMem(*i, DX_PLAYTYPE_BACK, false);
	}
	// 中身を空にする
	playSoundHandles_.clear();
}

int SoundPlayer::getSoundID(const SoundID & id) { return sounds_[id]; }
