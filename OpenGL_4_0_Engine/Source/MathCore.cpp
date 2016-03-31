#include "MathCore.h"
#include <assert.h>
#include <memory>

Matrix4x4::Matrix4x4()
{
	SetIdentity();
}

Matrix4x4::~Matrix4x4()
{
}

float Matrix4x4::Get(int row, int col)
{
	assert(row >= 0 && row < SIZE_ARRAY && col >= 0 && col < SIZE_ARRAY);

	return m_matrix[row][col];
}

void Matrix4x4::Set(int row, int col, float value)
{
	assert(row >= 0 && row < SIZE_ARRAY && col >= 0 && col < SIZE_ARRAY);

	m_matrix[row][col] = value;
}

float* Matrix4x4::AsArray()
{
	return (float*)m_matrix;
}

void Matrix4x4::SetIdentity()
{
	memset(&m_matrix, 0, sizeof(float) * SIZE_ARRAY * SIZE_ARRAY);

	m_matrix[0][0] = 1.0f;
	m_matrix[1][1] = 1.0f;
	m_matrix[2][2] = 1.0f;
	m_matrix[3][3] = 1.0f;
}

////////////////////////////////////////////////////////////////////////////////
//
//	Vector2
//
////////////////////////////////////////////////////////////////////////////////

Vector2::Vector2()
{
	m_x = m_y = 0.0f;
}

Vector2::Vector2(float _x, float _y)
{
	m_x = _x;
	m_y = _y;
}

////////////////////////////////////////////////////////////////////////////////
//
//	Vector3
//
////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3()
{
	m_x = m_y = m_z = 0.0f;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	m_x = _x;
	m_y = _y;
	m_z = _z;
}