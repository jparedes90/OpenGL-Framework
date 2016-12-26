#pragma once
#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H
#include "KeyBoardState.h"
#include "MouseState.h"
#include "../maths/MathCore.h"

class input_manager
{
private:
	KeyBoardState m_curKeyBoardState;
	KeyBoardState m_prevKeyBoardState;
	MouseState m_currentMouseState;
	MouseState m_prevMouseState;
	Vector2 m_mousePosition;
	Vector2 m_prevMousePosition;

public:
	input_manager(void);
	~input_manager(void);

	void Update();

	bool IsKeyDown(KeyPad::Keys key);
	bool IsKeyUp(KeyPad::Keys key);
	bool IsKeyHit(KeyPad::Keys key);
	bool IsKeyReleased(KeyPad::Keys key);

	bool IsButtonDown(Mouse::MousePad mouse);
	bool IsButtonUp(Mouse::MousePad mouse);
	bool IsButtonHit(Mouse::MousePad mouse);
	bool IsButtonReleased(Mouse::MousePad mouse);

	const Vector2& getMousePosition();
	const Vector2& getPrevMousePosition();

	void EventHandlerKeyDown(WPARAM wParam);
	void EventHandlerKeyUp(WPARAM wParam);

	void MouseEventLDown();
	void MouseEventLUp();
	void MouseEventRDown();
	void MouseEventRUp();

	void SetMouseOnScreen(bool mouseOnScreen, bool wrapArroundScreen);
};
#endif
