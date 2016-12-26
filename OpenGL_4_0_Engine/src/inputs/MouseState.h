#pragma once
#ifndef _MOUSE_STATE_H
#define _MOUSE_STATE_H
#include "Keys.h"
#include "../maths/MathCore.h"

class MouseState
{
private:
	bool mouseLButton;
	bool mouseRButton;
	bool m_keepMouseOnScreen;
	bool m_wrapMouseAroundScreen;
	POINT pt;
	bool m_init;
	Vector2 m_mousePosition;
	Vector2 m_prevMousePosition;

public:
	MouseState(void);
	~MouseState(void);

	void Update();
	bool IsButtonDown(Mouse::MousePad mouse);
	bool IsButtonUp(Mouse::MousePad mouse);

	const Vector2& getMousePosition();
	const Vector2& getPrevMousePosition();

	void MouseEventLDown();
	void MouseEventLUp();
	void MouseEventRDown();
	void MouseEventRUp();

	void SetMouseOnScreen(bool mouseOnScreen, bool wrapArroundScreen);
};
#endif
