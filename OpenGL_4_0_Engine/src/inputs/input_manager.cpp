#include "input_manager.h"
#include "../SystemDefs.h"

input_manager::input_manager(void)
{
	m_prevKeyBoardState = m_curKeyBoardState;
	m_prevMouseState = m_currentMouseState;
	m_mousePosition = m_prevMousePosition = Vector2(0, 0);
}

input_manager::~input_manager(void)
{
}

void input_manager::Update()
{
	m_prevKeyBoardState = m_curKeyBoardState;
	m_prevMouseState = m_currentMouseState;
	m_currentMouseState.Update();

	m_mousePosition = m_currentMouseState.getMousePosition();
	m_prevMousePosition = m_currentMouseState.getPrevMousePosition();
}

const Vector2& input_manager::getMousePosition()
{
	return m_mousePosition;
}

const Vector2& input_manager::getPrevMousePosition()
{
	return m_prevMousePosition;
}

bool input_manager::IsKeyDown(KeyPad::Keys key)
{
	return m_curKeyBoardState.IsKeyDown(key);
}
bool input_manager::IsKeyUp(KeyPad::Keys key)
{
	return m_curKeyBoardState.IsKeyUp(key);
}
bool input_manager::IsKeyHit(KeyPad::Keys key)
{
	return m_curKeyBoardState.IsKeyDown(key) && m_prevKeyBoardState.IsKeyUp(key);
}
bool input_manager::IsKeyReleased(KeyPad::Keys key)
{
	return m_curKeyBoardState.IsKeyUp(key) && m_prevKeyBoardState.IsKeyDown(key);
}
bool input_manager::IsButtonDown(Mouse::MousePad mouse)
{
	return m_currentMouseState.IsButtonDown(mouse);
}
bool input_manager::IsButtonUp(Mouse::MousePad mouse)
{
	return m_currentMouseState.IsButtonUp(mouse);
}
bool input_manager::IsButtonHit(Mouse::MousePad mouse)
{
	return m_currentMouseState.IsButtonDown(mouse) && m_prevMouseState.IsButtonUp(mouse);
}
bool input_manager::IsButtonReleased(Mouse::MousePad mouse)
{
	return m_currentMouseState.IsButtonUp(mouse) && m_prevMouseState.IsButtonDown(mouse);
}
void input_manager::EventHandlerKeyDown(WPARAM wParam)
{
	m_curKeyBoardState.EventHandlerDown(wParam);
}
void input_manager::EventHandlerKeyUp(WPARAM wParam)
{
	m_curKeyBoardState.EventHandlerUp(wParam);
}

void input_manager::MouseEventLDown()
{
	m_currentMouseState.MouseEventLDown();
}
void input_manager::MouseEventLUp()
{
	m_currentMouseState.MouseEventLUp();
}
void input_manager::MouseEventRDown()
{
	m_currentMouseState.MouseEventRDown();
}
void input_manager::MouseEventRUp()
{
	m_currentMouseState.MouseEventRUp();
}

void input_manager::SetMouseOnScreen(bool mouseOnScreen, bool wrapArroundScreen)
{
	m_currentMouseState.SetMouseOnScreen(mouseOnScreen, wrapArroundScreen);
}
