#include "RecTangle.h"

RecTangle::RecTangle(void)
{
}

RecTangle::RecTangle(float _left, float _top, float _width, float _height)
{
	m_left = _left;
	m_right = _left + _width;
	m_top = _top;
	m_bottom = m_top + _height;
	m_width = _width;
	m_height = _height;
}

RecTangle::~RecTangle(void)
{
}

void RecTangle::Set(float _left, float _top)
{
	m_left = _left;
	m_right = m_left + m_width;
	m_top = _top;
	m_bottom = m_top + m_height;
}

float RecTangle::GetLeft()
{
	return m_left;
}

float RecTangle::GetRight()
{
	return m_right;
}

float RecTangle::GetTop()
{
	return m_top;
}

float RecTangle::GetBottom()
{
	return m_bottom;
}

float RecTangle::GetWidth()
{
	return m_width;
}

float RecTangle::GetHeight()
{
	return m_height;
}
