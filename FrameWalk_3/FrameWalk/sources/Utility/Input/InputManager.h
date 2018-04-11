#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "KeyCode.h"

#include <unordered_map>
#include <string>

enum class ActionType;

class InputManager {
private:
	InputManager();
	~InputManager(){}

public:

	static InputManager& GetInstance();
	// �L�[���͏��
	int GetHitKeyFrameAll();
	// �L�[���͂̒ǉ�
	void RegistKeyCode();

	bool IsPushButton();

	bool IsKeyDown(KeyCode handle);
	bool IsKeyOn(KeyCode handle);
	bool IsKeyUp(KeyCode handle);

	bool IsButtonDown(PS2Buttons handle);
	bool IsButtonOn(PS2Buttons handle);
	bool IsButtonUp(PS2Buttons handle);

	bool isConnectGamePad();

private:
	static const int MAX_KEY_NUM = 256;

	unsigned int previous_key_state[MAX_KEY_NUM];
	unsigned int current_key_state[MAX_KEY_NUM];
	unsigned int previous_button_state;	// �ߋ��̃{�^���̏��
	unsigned int current_button_state;	// ���݂̃{�^���̏��

	//�L�[�R���t�B�O�p�L�[�f�[�^
	std::unordered_map<KeyCode, unsigned int> KeyName;
	std::unordered_map<PS2Buttons, unsigned int> ButtonName;
	std::unordered_map<PS2Buttons, KeyCode> ConnectInputName;
};

#endif