#include "InputManager.h"
#include "DxLib.h"

static const int MAX_BUTTON_NUM = 11;

InputManager::InputManager()
{
	RegistKeyCode();
}

InputManager & InputManager::GetInstance()
{
	static InputManager input;
	return input;
}

int InputManager::GetHitKeyFrameAll()
{
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);

	for (int i = 0; i < MAX_KEY_NUM; i++) {
		// キー状態の更新
		previous_key_state[i] = current_key_state[i];
		// 入力があったら、カウントを加算する
		if (GetHitKeyStateAll_Key[i] != 0)
			current_key_state[i]++;
		else current_key_state[i] = 0;
	}
	previous_button_state = current_button_state;
	current_button_state = GetJoypadInputState(DX_INPUT_PAD1);

	return 0;
}

void InputManager::RegistKeyCode()
{
	// キーコードの取得
	KeyName[KeyCode::UP] = KEY_INPUT_UP;
	KeyName[KeyCode::DOWN] = KEY_INPUT_DOWN;
	KeyName[KeyCode::RIGHT] = KEY_INPUT_RIGHT;
	KeyName[KeyCode::LEFT] = KEY_INPUT_LEFT;
	KeyName[KeyCode::ESCAPE] = KEY_INPUT_ESCAPE;
	KeyName[KeyCode::SPACE] = KEY_INPUT_SPACE;
	KeyName[KeyCode::RETURN] = KEY_INPUT_RETURN;
	KeyName[KeyCode::A] = KEY_INPUT_A;
	KeyName[KeyCode::B] = KEY_INPUT_B;
	KeyName[KeyCode::C] = KEY_INPUT_C;
	KeyName[KeyCode::D] = KEY_INPUT_D;
	KeyName[KeyCode::E] = KEY_INPUT_E;
	KeyName[KeyCode::F] = KEY_INPUT_F;
	KeyName[KeyCode::G] = KEY_INPUT_G;
	KeyName[KeyCode::H] = KEY_INPUT_H;
	KeyName[KeyCode::I] = KEY_INPUT_I;
	KeyName[KeyCode::J] = KEY_INPUT_J;
	KeyName[KeyCode::K] = KEY_INPUT_K;
	KeyName[KeyCode::L] = KEY_INPUT_L;
	KeyName[KeyCode::M] = KEY_INPUT_M;
	KeyName[KeyCode::N] = KEY_INPUT_N;
	KeyName[KeyCode::O] = KEY_INPUT_O;
	KeyName[KeyCode::P] = KEY_INPUT_P;
	KeyName[KeyCode::Q] = KEY_INPUT_Q;
	KeyName[KeyCode::R] = KEY_INPUT_R;
	KeyName[KeyCode::S] = KEY_INPUT_S;
	KeyName[KeyCode::T] = KEY_INPUT_T;
	KeyName[KeyCode::U] = KEY_INPUT_U;
	KeyName[KeyCode::V] = KEY_INPUT_V;
	KeyName[KeyCode::W] = KEY_INPUT_W;
	KeyName[KeyCode::X] = KEY_INPUT_X;
	KeyName[KeyCode::Y] = KEY_INPUT_Y;
	KeyName[KeyCode::Z] = KEY_INPUT_Z;
	KeyName[KeyCode::L_SHIFT] = KEY_INPUT_LSHIFT;
	KeyName[KeyCode::R_SHIFT] = KEY_INPUT_RSHIFT;
	// PS2コントローラーのボタンの取得
	ButtonName[PS2Buttons::BUTTON_CIRCLE] = PAD_INPUT_2;
	ButtonName[PS2Buttons::BUTTON_CROSS] = PAD_INPUT_3;
	ButtonName[PS2Buttons::BUTTON_START] = PAD_INPUT_9;
	ButtonName[PS2Buttons::BUTTON_SELECT] = PAD_INPUT_10;
	ButtonName[PS2Buttons::BUTTON_L1] = PAD_INPUT_7;
	ButtonName[PS2Buttons::BUTTON_R1] = PAD_INPUT_8;
	ButtonName[PS2Buttons::BUTTON_L2] = PAD_INPUT_5;
	ButtonName[PS2Buttons::BUTTON_R2] = PAD_INPUT_6;
	ButtonName[PS2Buttons::BUTTON_UP] = PAD_INPUT_UP;
	ButtonName[PS2Buttons::BUTTON_DOWN] = PAD_INPUT_DOWN;
	ButtonName[PS2Buttons::BUTTON_RIGHT] = PAD_INPUT_RIGHT;
	ButtonName[PS2Buttons::BUTTON_LEFT] = PAD_INPUT_LEFT;

	////ボタンとキーコードの関連付け
	//ConnectInputName[BUTTON_L1] = KeyCode::L_SHIFT;
	//ConnectInputName[BUTTON_R1] = KeyCode::R_SHIFT;
	//ConnectInputName[BUTTON_L2] = KeyCode::Q;
	//ConnectInputName[BUTTON_R2] = KeyCode::L;
	//ConnectInputName[BUTTON_CIRCLE] = KeyCode::SPACE;
	//ConnectInputName[BUTTON_CROSS] = KeyCode::X;
	//ConnectInputName[BUTTON_START] = KeyCode::T;
	//ConnectInputName[BUTTON_UP] = KeyCode::UP;
	//ConnectInputName[BUTTON_DOWN] = KeyCode::DOWN;
	//ConnectInputName[BUTTON_RIGHT] = KeyCode::RIGHT;
	//ConnectInputName[BUTTON_LEFT] = KeyCode::LEFT;
}

bool InputManager::IsPushButton()
{
	for (auto i : current_key_state) {
		if (i != 0) return true;
	}
	for (auto i : ButtonName) {
		if (i.first == BUTTON_UP || i.first == BUTTON_DOWN || 
			i.first == BUTTON_RIGHT || i.first == BUTTON_LEFT)
			continue;
		if ((current_button_state & i.second) != 0)
			return true;
	}
	return false;
}

bool InputManager::IsKeyDown(KeyCode handle)
{
	if (previous_key_state[KeyName[handle]] == 0 && 
		current_key_state[KeyName[handle]] == 1) 
		return true;
	return false;
}

bool InputManager::IsKeyOn(KeyCode handle)
{
	// 過去の状態が押されている
	if (previous_key_state[KeyName[handle]] != 0 && 
		current_key_state[KeyName[handle]] != 0) 
		return true;
	return false;
}

bool InputManager::IsKeyUp(KeyCode handle)
{
	if (previous_key_state[KeyName[handle]] != 0 && 
		current_key_state[KeyName[handle]] == 0) 
		return true;
	return false;
}

bool InputManager::IsButtonDown(PS2Buttons handle)
{
	if ((previous_button_state & ButtonName[handle]) == 0 &&
		(current_button_state & ButtonName[handle]) != 0)
		return true;
	else return IsKeyDown(ConnectInputName[handle]);
}

bool InputManager::IsButtonOn(PS2Buttons handle)
{
	if ((previous_button_state & ButtonName[handle]) != 0 && 
		(current_button_state & ButtonName[handle]) != 0)
		return true;
	else return IsKeyOn(ConnectInputName[handle]);
}

bool InputManager::IsButtonUp(PS2Buttons handle)
{
	if ((previous_button_state & ButtonName[handle]) != 0 && 
		(current_button_state & ButtonName[handle]) == 0)
		return true;
	else return IsKeyUp(ConnectInputName[handle]);
}

bool InputManager::isConnectGamePad()
{
	if (GetJoypadNum() != 0) return true;
	return false;
}
