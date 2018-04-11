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
	// �T�E���h�̒ǉ�
	void addSound(const SoundID & id, const int handle, const bool isStopSound);
	// �ꎞ��~������T�E���h��
	/*void addSound(
	const SoundID& id, const char* fileName,
	const bool isStopSound = false);*/
	// �T�E���h�̍Đ�
	void playSound(const SoundID id);
	// �T�E���h�̍Đ�(���[�v)
	void playLoopSound(const SoundID id);
	// �T�E���h�̒�~
	void stopSound(const SoundID id);
	// �S�ẴT�E���h�̒�~
	void stopAllSound();
	// �T�E���h�̈ꎞ��~���s���܂�
	void poseStopSound();
	// �ꎞ��~�����T�E���h���Đ����܂�
	void poseRestartSound();
	// �T�E���hID���擾���܂�
	int getSoundID(const SoundID& id);

private:
	// �T�E���h�}�b�v
	std::unordered_map<SoundID, int> sounds_;
	// ��~�T�E���h�n���h���R���e�i
	typedef std::list<int> StopSoundContainer;
	StopSoundContainer stopSoundHandles_;
	// �Đ��T�E���h�n���h���R���e�i
	typedef std::list<int> PlaySoundContainer;
	PlaySoundContainer playSoundHandles_;
};

#endif