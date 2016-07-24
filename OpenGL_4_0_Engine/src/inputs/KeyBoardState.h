#pragma once
#ifndef _KEYBOARD_STATE_H
#define _KEYBOARD_STATE_H
#include "Keys.h"

class KeyBoardState
{
	bool keys[256];
public:
	KeyBoardState(void);
	~KeyBoardState(void);

	bool IsKeyUp(KeyPad::Keys key);
	bool IsKeyDown(KeyPad::Keys key);

	void EventHandlerDown(WPARAM wParam);
	void EventHandlerUp(WPARAM wParam);
};
#endif
