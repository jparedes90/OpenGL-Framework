#ifndef _MATH_CORE_H_
#define _MATH_CORE_H_

#define SIZE_ARRAY 4

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	float Get(int row, int col);
	void Set(int row, int col, float value);
	void SetIdentity();

	float* AsArray();

private:
	float m_matrix[SIZE_ARRAY][SIZE_ARRAY];
};


class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);

	float GetX() { return m_x; }
	float GetY() { return m_y; }

private:
	float m_x;
	float m_y;
};

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);

	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetZ() { return m_z; }

private:
	float m_x;
	float m_y;
	float m_z;
};

#endif