#include "MouseState.h"
#include "../SystemDefs.h"

MouseState::MouseState(void)
{
	pt.x = pt.y = (LONG)0.0f;
	m_mousePosition = m_prevMousePosition = Vector2(0,0);
	ShowCursor(false);
	m_init = false;
	mouseLButton = false;
	mouseRButton = false;
	m_keepMouseOnScreen = false;
	m_wrapMouseAroundScreen = false;
}

MouseState::~MouseState(void)
{
}

bool MouseState::IsButtonDown(Mouse::MousePad mouse)
{
	return (mouse == WM_LBUTTONDOWN && mouseLButton == true) || (mouse == WM_RBUTTONDOWN && mouseRButton == true);
}
bool MouseState::IsButtonUp(Mouse::MousePad mouse)
{
	return (mouse == WM_LBUTTONDOWN && mouseLButton == false) || (mouse == WM_RBUTTONDOWN && mouseRButton == false);
}

void MouseState::MouseEventLDown()
{
	mouseLButton = true;
}
void MouseState::MouseEventLUp()
{
	mouseLButton = false;
}

void MouseState::MouseEventRDown()
{
	mouseRButton = true;
}
void MouseState::MouseEventRUp()
{
	mouseRButton = false;
}
void MouseState::Update()
{
	if(m_init== false)
	{
		SetCursorPos((int)(WIND_POSX + (SCREEN_WIDTH/2.0f)), (int)(WIND_POSY + (SCREEN_HEIGHT/2.0f)));
		m_init = true;
		return;
	}
	m_prevMousePosition = m_mousePosition;
	GetCursorPos(&pt);

	if(m_keepMouseOnScreen)
	{
		if(pt.x < WIND_POSX + 5)
		{
			if(!m_wrapMouseAroundScreen)
			{
				pt.x = WIND_POSX + SCREEN_WIDTH - 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetX((float)pt.x - WIND_POSX);
			}
			else
			{
				pt.x = WIND_POSX + 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetX((float)pt.x - WIND_POSX);
			}
		}
		else if(pt.x > WIND_POSX + SCREEN_WIDTH - 5)
		{
			if(!m_wrapMouseAroundScreen)
			{
				pt.x = WIND_POSX + 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetX((float)pt.x - WIND_POSX);
			}
			else
			{
				pt.x = WIND_POSX + SCREEN_WIDTH - 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetX((float)pt.x - WIND_POSX);
			}
		}
		if(pt.y < WIND_POSY + 5)
		{
			if(!m_wrapMouseAroundScreen)
			{
				pt.y = WIND_POSY + SCREEN_HEIGHT - 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetY((float)pt.y - WIND_POSY);
			}
			else
			{
				pt.y = WIND_POSY + 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetY((float)pt.y - WIND_POSY);
			}
		}
		else if(pt.y > WIND_POSY + SCREEN_HEIGHT - 5)
		{
			if(!m_wrapMouseAroundScreen)
			{
				pt.y = WIND_POSY + 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetY((float)pt.y - WIND_POSY);
			}
			else
			{
				pt.y = WIND_POSY + SCREEN_HEIGHT - 5;
				SetCursorPos(pt.x, pt.y);
				m_prevMousePosition.SetY((float)pt.y - WIND_POSY);
			}
		}
	}

	m_mousePosition.Set((float)pt.x - WIND_POSX, (float)pt.y - WIND_POSY);
}

const Vector2& MouseState::getMousePosition()
{
	return m_mousePosition;
}

const Vector2& MouseState::getPrevMousePosition()
{
	return m_prevMousePosition;
}

void MouseState::SetMouseOnScreen(bool mouseOnScreen, bool wrapArroundScreen)
{
	m_keepMouseOnScreen = mouseOnScreen;
	m_wrapMouseAroundScreen = wrapArroundScreen;
}
