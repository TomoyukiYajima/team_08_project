#ifndef KEYCODE_H_
#define KEYCODE_H_

// キー入力用コード
enum KeyCode {
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ESCAPE,
	SPACE,
	RETURN,
	A, B, C, D, E, F, G,
	H, I, J, K, L, M, N,
	O, P, Q, R, S, T, U,
	V, W, X, Y, Z,
	L_SHIFT,
	R_SHIFT
};

// PS2コントローラー用コード
enum PS2Buttons {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_RIGHT,
	BUTTON_LEFT,
	BUTTON_CIRCLE,
	BUTTON_CROSS,
	BUTTON_START,
	BUTTON_L1,
	BUTTON_R1,
	BUTTON_L2,
	BUTTON_R2,
	BUTTON_SELECT
};

#endif