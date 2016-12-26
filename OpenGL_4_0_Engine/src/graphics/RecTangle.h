//#pragma once
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

class RecTangle
{
public:
	RecTangle(void);
	RecTangle(float _left, float _top, float _width, float _height);
	~RecTangle(void);
	
	void Set(float _left, float _top);

	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	float GetWidth();
	float GetHeight();
private:
	float m_left, m_right, m_top, m_bottom, m_width, m_height;
};
#endif
