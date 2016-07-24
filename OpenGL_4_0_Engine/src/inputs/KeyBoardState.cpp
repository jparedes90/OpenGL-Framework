#include "KeyBoardState.h"

KeyBoardState::KeyBoardState(void)
{
	for(int i = 0; i < 256; ++i)
	{
		keys[i] = false;
	}
}
KeyBoardState::~KeyBoardState(void)
{
}

bool KeyBoardState::IsKeyDown(KeyPad::Keys key)
{
	return (keys[key] == true);
}

bool KeyBoardState::IsKeyUp(KeyPad::Keys key)
{
	return (keys[key] == false);
}

void KeyBoardState::EventHandlerDown(WPARAM wParam)
{
	keys[wParam] = true;
}
void KeyBoardState::EventHandlerUp(WPARAM wParam)
{
	keys[wParam] = false;
}
