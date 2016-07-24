#include "MathCore.h"
#include <assert.h>
#include <memory>
#include <math.h>

Matrix4x4::Matrix4x4()
{
	SetIdentity();
}

Matrix4x4::~Matrix4x4()
{
}

Matrix4x4 Matrix4x4::operator *(const Matrix4x4 &mat)
{
	Matrix4x4 temp;

	temp.m_matrix[0][0] = (this->m_matrix[0][0] * mat.m_matrix[0][0]) + (this->m_matrix[0][1] * mat.m_matrix[1][0]) + (this->m_matrix[0][2] * mat.m_matrix[2][0]) + (this->m_matrix[0][3] * mat.m_matrix[3][0]);
	temp.m_matrix[0][1] = (this->m_matrix[0][0] * mat.m_matrix[0][1]) + (this->m_matrix[0][1] * mat.m_matrix[1][1]) + (this->m_matrix[0][2] * mat.m_matrix[2][1]) + (this->m_matrix[0][3] * mat.m_matrix[3][1]);
	temp.m_matrix[0][2] = (this->m_matrix[0][0] * mat.m_matrix[0][2]) + (this->m_matrix[0][1] * mat.m_matrix[1][2]) + (this->m_matrix[0][2] * mat.m_matrix[2][2]) + (this->m_matrix[0][3] * mat.m_matrix[3][2]);
	temp.m_matrix[0][3] = (this->m_matrix[0][0] * mat.m_matrix[0][3]) + (this->m_matrix[0][1] * mat.m_matrix[1][3]) + (this->m_matrix[0][2] * mat.m_matrix[2][3]) + (this->m_matrix[0][3] * mat.m_matrix[3][3]);

	temp.m_matrix[1][0] = (this->m_matrix[1][0] * mat.m_matrix[0][0]) + (this->m_matrix[1][1] * mat.m_matrix[1][0]) + (this->m_matrix[1][2] * mat.m_matrix[2][0]) + (this->m_matrix[1][3] * mat.m_matrix[3][0]);
	temp.m_matrix[1][1] = (this->m_matrix[1][0] * mat.m_matrix[0][1]) + (this->m_matrix[1][1] * mat.m_matrix[1][1]) + (this->m_matrix[1][2] * mat.m_matrix[2][1]) + (this->m_matrix[1][3] * mat.m_matrix[3][1]);
	temp.m_matrix[1][2] = (this->m_matrix[1][0] * mat.m_matrix[0][2]) + (this->m_matrix[1][1] * mat.m_matrix[1][2]) + (this->m_matrix[1][2] * mat.m_matrix[2][2]) + (this->m_matrix[1][3] * mat.m_matrix[3][2]);
	temp.m_matrix[1][3] = (this->m_matrix[1][0] * mat.m_matrix[0][3]) + (this->m_matrix[1][1] * mat.m_matrix[1][3]) + (this->m_matrix[1][2] * mat.m_matrix[2][3]) + (this->m_matrix[1][3] * mat.m_matrix[3][3]);

	temp.m_matrix[2][0] = (this->m_matrix[2][0] * mat.m_matrix[0][0]) + (this->m_matrix[2][1] * mat.m_matrix[1][0]) + (this->m_matrix[2][2] * mat.m_matrix[2][0]) + (this->m_matrix[2][3] * mat.m_matrix[3][0]);
	temp.m_matrix[2][1] = (this->m_matrix[2][0] * mat.m_matrix[0][1]) + (this->m_matrix[2][1] * mat.m_matrix[1][1]) + (this->m_matrix[2][2] * mat.m_matrix[2][1]) + (this->m_matrix[2][3] * mat.m_matrix[3][1]);
	temp.m_matrix[2][2] = (this->m_matrix[2][0] * mat.m_matrix[0][2]) + (this->m_matrix[2][1] * mat.m_matrix[1][2]) + (this->m_matrix[2][2] * mat.m_matrix[2][2]) + (this->m_matrix[2][3] * mat.m_matrix[3][2]);
	temp.m_matrix[2][3] = (this->m_matrix[2][0] * mat.m_matrix[0][3]) + (this->m_matrix[2][1] * mat.m_matrix[1][3]) + (this->m_matrix[2][2] * mat.m_matrix[2][3]) + (this->m_matrix[2][3] * mat.m_matrix[3][3]);

	temp.m_matrix[3][0] = (this->m_matrix[3][0] * mat.m_matrix[0][0]) + (this->m_matrix[3][1] * mat.m_matrix[1][0]) + (this->m_matrix[3][2] * mat.m_matrix[2][0]) + (this->m_matrix[3][3] * mat.m_matrix[3][0]);
	temp.m_matrix[3][1] = (this->m_matrix[3][0] * mat.m_matrix[0][1]) + (this->m_matrix[3][1] * mat.m_matrix[1][1]) + (this->m_matrix[3][2] * mat.m_matrix[2][1]) + (this->m_matrix[3][3] * mat.m_matrix[3][1]);
	temp.m_matrix[3][2] = (this->m_matrix[3][0] * mat.m_matrix[0][2]) + (this->m_matrix[3][1] * mat.m_matrix[1][2]) + (this->m_matrix[3][2] * mat.m_matrix[2][2]) + (this->m_matrix[3][3] * mat.m_matrix[3][2]);
	temp.m_matrix[3][3] = (this->m_matrix[3][0] * mat.m_matrix[0][3]) + (this->m_matrix[3][1] * mat.m_matrix[1][3]) + (this->m_matrix[3][2] * mat.m_matrix[2][3]) + (this->m_matrix[3][3] * mat.m_matrix[3][3]);

	return temp;
}

Matrix4x4 Matrix4x4::operator *(const float value)
{
	Matrix4x4 temp = *this;
	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] *= value;
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator *=(const Matrix4x4 &mat)
{
	Matrix4x4 temp;
	temp.m_matrix[0][0] = (this->m_matrix[0][0] * mat.m_matrix[0][0]) + (this->m_matrix[0][1] * mat.m_matrix[1][0]) + (this->m_matrix[0][2] * mat.m_matrix[2][0]) + (this->m_matrix[0][3] * mat.m_matrix[3][0]);
	temp.m_matrix[0][1] = (this->m_matrix[0][0] * mat.m_matrix[0][1]) + (this->m_matrix[0][1] * mat.m_matrix[1][1]) + (this->m_matrix[0][2] * mat.m_matrix[2][1]) + (this->m_matrix[0][3] * mat.m_matrix[3][1]);
	temp.m_matrix[0][2] = (this->m_matrix[0][0] * mat.m_matrix[0][2]) + (this->m_matrix[0][1] * mat.m_matrix[1][2]) + (this->m_matrix[0][2] * mat.m_matrix[2][2]) + (this->m_matrix[0][3] * mat.m_matrix[3][2]);
	temp.m_matrix[0][3] = (this->m_matrix[0][0] * mat.m_matrix[0][3]) + (this->m_matrix[0][1] * mat.m_matrix[1][3]) + (this->m_matrix[0][2] * mat.m_matrix[2][3]) + (this->m_matrix[0][3] * mat.m_matrix[3][3]);

	temp.m_matrix[1][0] = (this->m_matrix[1][0] * mat.m_matrix[0][0]) + (this->m_matrix[1][1] * mat.m_matrix[1][0]) + (this->m_matrix[1][2] * mat.m_matrix[2][0]) + (this->m_matrix[1][3] * mat.m_matrix[3][0]);
	temp.m_matrix[1][1] = (this->m_matrix[1][0] * mat.m_matrix[0][1]) + (this->m_matrix[1][1] * mat.m_matrix[1][1]) + (this->m_matrix[1][2] * mat.m_matrix[2][1]) + (this->m_matrix[1][3] * mat.m_matrix[3][1]);
	temp.m_matrix[1][2] = (this->m_matrix[1][0] * mat.m_matrix[0][2]) + (this->m_matrix[1][1] * mat.m_matrix[1][2]) + (this->m_matrix[1][2] * mat.m_matrix[2][2]) + (this->m_matrix[1][3] * mat.m_matrix[3][2]);
	temp.m_matrix[1][3] = (this->m_matrix[1][0] * mat.m_matrix[0][3]) + (this->m_matrix[1][1] * mat.m_matrix[1][3]) + (this->m_matrix[1][2] * mat.m_matrix[2][3]) + (this->m_matrix[1][3] * mat.m_matrix[3][3]);

	temp.m_matrix[2][0] = (this->m_matrix[2][0] * mat.m_matrix[0][0]) + (this->m_matrix[2][1] * mat.m_matrix[1][0]) + (this->m_matrix[2][2] * mat.m_matrix[2][0]) + (this->m_matrix[2][3] * mat.m_matrix[3][0]);
	temp.m_matrix[2][1] = (this->m_matrix[2][0] * mat.m_matrix[0][1]) + (this->m_matrix[2][1] * mat.m_matrix[1][1]) + (this->m_matrix[2][2] * mat.m_matrix[2][1]) + (this->m_matrix[2][3] * mat.m_matrix[3][1]);
	temp.m_matrix[2][2] = (this->m_matrix[2][0] * mat.m_matrix[0][2]) + (this->m_matrix[2][1] * mat.m_matrix[1][2]) + (this->m_matrix[2][2] * mat.m_matrix[2][2]) + (this->m_matrix[2][3] * mat.m_matrix[3][2]);
	temp.m_matrix[2][3] = (this->m_matrix[2][0] * mat.m_matrix[0][3]) + (this->m_matrix[2][1] * mat.m_matrix[1][3]) + (this->m_matrix[2][2] * mat.m_matrix[2][3]) + (this->m_matrix[2][3] * mat.m_matrix[3][3]);

	temp.m_matrix[3][0] = (this->m_matrix[3][0] * mat.m_matrix[0][0]) + (this->m_matrix[3][1] * mat.m_matrix[1][0]) + (this->m_matrix[3][2] * mat.m_matrix[2][0]) + (this->m_matrix[3][3] * mat.m_matrix[3][0]);
	temp.m_matrix[3][1] = (this->m_matrix[3][0] * mat.m_matrix[0][1]) + (this->m_matrix[3][1] * mat.m_matrix[1][1]) + (this->m_matrix[3][2] * mat.m_matrix[2][1]) + (this->m_matrix[3][3] * mat.m_matrix[3][1]);
	temp.m_matrix[3][2] = (this->m_matrix[3][0] * mat.m_matrix[0][2]) + (this->m_matrix[3][1] * mat.m_matrix[1][2]) + (this->m_matrix[3][2] * mat.m_matrix[2][2]) + (this->m_matrix[3][3] * mat.m_matrix[3][2]);
	temp.m_matrix[3][3] = (this->m_matrix[3][0] * mat.m_matrix[0][3]) + (this->m_matrix[3][1] * mat.m_matrix[1][3]) + (this->m_matrix[3][2] * mat.m_matrix[2][3]) + (this->m_matrix[3][3] * mat.m_matrix[3][3]);

	return temp;
}

//Matrix4x4 Matrix4x4::operator *(const IGSRVector3& vec)
//{
//	IGSRVector3 vecTemp = vec;
//	Matrix4x4 temp = *this;
//
//	temp.m_matrix[0][0] *= vecTemp.GetX();
//	temp.m_matrix[0][1] *= vecTemp.GetY();
//	temp.m_matrix[0][2] *= vecTemp.GetZ();
//
//	temp.m_matrix[1][0] *= vecTemp.GetX();
//	temp.m_matrix[1][1] *= vecTemp.GetY();
//	temp.m_matrix[1][2] *= vecTemp.GetZ();
//
//	temp.m_matrix[2][0] *= vecTemp.GetX();
//	temp.m_matrix[2][1] *= vecTemp.GetY();
//	temp.m_matrix[2][2] *= vecTemp.GetZ();
//
//	return temp;
//
//}

Matrix4x4 Matrix4x4::operator *=(const float value)
{
	Matrix4x4 temp = *this;

	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] *= value;
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator +(const Matrix4x4 &mat)
{
	Matrix4x4 temp = *this;
	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] += mat.m_matrix[i][j];
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator +(const float value)
{
	Matrix4x4 temp = *this;
	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] += value;
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator +=(const Matrix4x4 &mat)
{
	Matrix4x4 temp = *this;

	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] += mat.m_matrix[i][j];
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator +=(const float value)
{
	Matrix4x4 temp = *this;

	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] += value;
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator -(const Matrix4x4 &mat)
{
	Matrix4x4 temp = *this;
	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] -= mat.m_matrix[i][j];
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator -=(const Matrix4x4 &mat)
{
	Matrix4x4 temp = *this;

	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] -= mat.m_matrix[i][j];
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator -(const float value)
{
	Matrix4x4 temp = *this;

	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] -= value;
		}
	}

	return temp;
}

Matrix4x4 Matrix4x4::operator -=(const float value)
{
	Matrix4x4 temp = *this;

	for (unsigned int i = 0; i < SIZE_ARRAY; i++)
	{
		for (unsigned int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.m_matrix[i][j] -= value;
		}
	}

	return temp;
}

Vector3 Matrix4x4::operator*(const Vector3& v)
{
	// [a b c x][X] 
	// [d e f y][Y] = [aX+bY+cZ+x dX+eY+fZ+y gX+hY+iZ+z]
	// [g h i z][Z]
	//          [1]

	Vector3 vecResult, _v = v;
	vecResult.Set(m_matrix[0][0] * _v.GetX() + m_matrix[1][0] * _v.GetY() + m_matrix[2][0] * _v.GetZ() + m_matrix[3][0],
		m_matrix[0][1] * _v.GetX() + m_matrix[1][1] * _v.GetY() + m_matrix[2][1] * _v.GetZ() + m_matrix[3][1],
		m_matrix[0][2] * _v.GetX() + m_matrix[1][2] * _v.GetY() + m_matrix[2][2] * _v.GetZ() + m_matrix[3][2]);

	return vecResult;
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

void Matrix4x4::BuildRotationAboutAxis(const Vector3& pAxis, float pAngle)
{
	Vector3 oAxis = pAxis;
	float radians = pAngle * (float)PIOVER180;

	float fCosTheta = cosf(radians);
	float fSinTheta = sinf(radians);

	SetIdentity();

	this->Set(0, 0, fCosTheta + (1.0f - fCosTheta) * (oAxis.GetX() * oAxis.GetX()));
	this->Set(1, 0, (1.0f - fCosTheta)*(oAxis.GetX() * oAxis.GetY()) + (fSinTheta * oAxis.GetZ()));
	this->Set(2, 0, (1.0f - fCosTheta)*(oAxis.GetX() * oAxis.GetZ()) - (fSinTheta * oAxis.GetY()));
	this->Set(0, 1, (1.0f - fCosTheta)*(oAxis.GetX() * oAxis.GetY()) - (fSinTheta * oAxis.GetZ()));
	this->Set(1, 1, fCosTheta + (1.0f - fCosTheta) * (oAxis.GetY() * oAxis.GetY()));
	this->Set(2, 1, (1.0f - fCosTheta)*(oAxis.GetY() * oAxis.GetZ()) + (fSinTheta * oAxis.GetX()));
	this->Set(0, 2, (1.0f - fCosTheta)*(oAxis.GetX() * oAxis.GetZ()) + (fSinTheta * oAxis.GetY()));
	this->Set(1, 2, (1.0f - fCosTheta)*(oAxis.GetY() * oAxis.GetZ()) - (fSinTheta * oAxis.GetX()));
	this->Set(2, 2, fCosTheta + (1.0f - fCosTheta) * (oAxis.GetZ() * oAxis.GetZ()));
}

void Matrix4x4::BuildRotationX(float pAngle)
{
	float radians = pAngle * (float)PIOVER180;

	SetIdentity();
	Set(1, 1, cosf(radians));
	Set(1, 2, -sinf(radians));
	Set(2, 1, sinf(radians));
	Set(2, 2, cosf(radians));
}

void Matrix4x4::BuildRotationY(float pAngle)
{
	float radians = pAngle * (float)PIOVER180;

	SetIdentity();
	Set(0, 0, cosf(radians));
	Set(0, 2, sinf(radians));
	Set(2, 0, -sinf(radians));
	Set(2, 2, cosf(radians));
}

void Matrix4x4::BuildRotationZ(float pAngle)
{
	float radians = pAngle * (float)PIOVER180;

	SetIdentity();
	Set(0, 0, cosf(radians));
	Set(0, 1, -sinf(radians));
	Set(1, 0, sinf(radians));
	Set(1, 1, cosf(radians));
}

void Matrix4x4::BuildTranslation(float x, float y, float z)
{
	SetIdentity();

	Set(0, 3, x);
	Set(1, 3, y);
	Set(2, 3, z);
}

void Matrix4x4::BuildTranslation(const Vector3& translation)
{
	SetIdentity();

	Vector3 temp = translation;

	Set(0, 3, temp.GetX());
	Set(1, 3, temp.GetY());
	Set(2, 3, temp.GetZ());
}

void Matrix4x4::BuildScale(float x, float y, float z)
{
	SetIdentity();
	Set(0, 0, x);
	Set(1, 1, y);
	Set(2, 2, z);
}

void Matrix4x4::transform(Vector3 &oPoint)
{
	float fX = oPoint.GetX();
	float fY = oPoint.GetY();
	float fZ = oPoint.GetZ();

	oPoint.SetX(fX * this->m_matrix[0][0] + fY * this->m_matrix[0][1] + fZ * this->m_matrix[0][2] + this->m_matrix[0][3]);
	oPoint.SetY(fX * this->m_matrix[1][0] + fY * this->m_matrix[1][1] + fZ * this->m_matrix[1][2] + this->m_matrix[1][3]);
	oPoint.SetZ(fX * this->m_matrix[2][0] + fY * this->m_matrix[2][1] + fZ * this->m_matrix[2][2] + this->m_matrix[2][3]);
}


////////////////////////////////////////////////////////////////////////////////
//
//	Vector2
//
////////////////////////////////////////////////////////////////////////////////

Vector2::Vector2()
{
	m_x = 0.0f;
	m_y = 0.0f;
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

//Vector3::Vector3()
//{
//	Set(0.0f, 0.0f, 0.0f);
//}

Vector3::Vector3(float _x, float _y, float _z)
{
	Set(_x, _y, _z);
}

Vector3::~Vector3()
{}

Vector3 Vector3::operator+(const Vector3& vec)
{
	Vector3 temp = *this;
	temp.m_x += vec.m_x;
	temp.m_y += vec.m_y;
	temp.m_z += vec.m_z;

	return temp;
}

Vector3 Vector3::operator+=(const Vector3& vec)
{
	this->m_x += vec.m_x;
	this->m_y += vec.m_y;
	this->m_z += vec.m_z;

	Vector3 temp = *this;

	return temp;
}

Vector3 Vector3::operator-(const Vector3& vec)
{
	Vector3 temp = *this;
	temp.m_x -= vec.m_x;
	temp.m_y -= vec.m_y;
	temp.m_z -= vec.m_z;

	return temp;
}

Vector3 Vector3::operator-=(const Vector3& vec)
{
	this->m_x -= vec.m_x;
	this->m_y -= vec.m_y;
	this->m_z -= vec.m_z;

	return *this;
}

Vector3 Vector3::operator*(const Vector3& vec)
{
	Vector3 temp = *this;
	temp.m_x *= vec.m_x;
	temp.m_y *= vec.m_y;
	temp.m_z *= vec.m_z;

	return temp;
}

Vector3 Vector3::operator*(const float& scalar)
{
	Vector3 temp = *this;
	temp.m_x *= scalar;
	temp.m_y *= scalar;
	temp.m_z *= scalar;

	return temp;
}

Vector3 Vector3::operator*=(const Vector3& vec)
{
	this->m_x *= vec.m_x;
	this->m_y *= vec.m_y;
	this->m_z *= vec.m_z;

	return *this;
}

Vector3 Vector3::operator*=(const float& scalar)
{
	this->m_x *= scalar;
	this->m_y *= scalar;
	this->m_z *= scalar;

	return *this;
}

Vector3 Vector3::operator/(const Vector3& vec)
{
	Vector3 temp = *this;
	temp.m_x /= vec.m_x;
	temp.m_y /= vec.m_y;
	temp.m_z /= vec.m_z;

	return temp;
}

Vector3 Vector3::operator/(const float& scalar)
{
	Vector3 temp = *this;
	temp.m_x /= scalar;
	temp.m_y /= scalar;
	temp.m_z /= scalar;

	return temp;
}

Vector3 Vector3::operator/=(const Vector3& vec)
{
	this->m_x /= vec.m_x;
	this->m_y /= vec.m_y;
	this->m_z /= vec.m_z;

	return *this;
}

Vector3 Vector3::operator/=(const float& scalar)
{
	this->m_x /= scalar;
	this->m_y /= scalar;
	this->m_z /= scalar;

	return *this;
}

float Vector3::Dot(const Vector3& vec)const
{
	float dot = this->m_x * vec.m_x + this->m_y * vec.m_y + this->m_z * vec.m_z;

	return dot;
}

float Vector3::Length()const
{
	float length = sqrtf(this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z);

	return length;
}

float Vector3::LengthSqr()const
{
	float length = this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z;

	return length;
}

void Vector3::Normalize()
{
	float length = Length();

	//make sure we dont divide by zero
	if (length == 0.0f)
	{
		this->m_x = 0.0f;
		this->m_y = 0.0f;
		this->m_z = 0.0f;

		return;
	}

	this->m_x /= length;
	this->m_y /= length;
	this->m_z /= length;
}

Vector3 Vector3::Cross(const Vector3& vec1, const Vector3& vec2)
{
	Vector3 newVec;

	newVec.m_x = (vec1.m_y * vec2.m_z) - (vec1.m_z * vec2.m_y);
	newVec.m_y = (vec1.m_z * vec2.m_x) - (vec1.m_x * vec2.m_z);
	newVec.m_z = (vec1.m_x * vec2.m_y) - (vec1.m_y * vec2.m_x);

	return newVec;
}

const float& Vector3::GetX()const
{
	return this->m_x;
}

const float& Vector3::GetY()const
{
	return this->m_y;
}

const float& Vector3::GetZ()const
{
	return this->m_z;
}

void Vector3::Set(float _x, float _y, float _z)
{
	this->m_x = _x;
	this->m_y = _y;
	this->m_z = _z;
}

void Vector3::SetX(float _x)
{
	this->m_x = _x;
}

void Vector3::SetY(float _y)
{
	this->m_y = _y;
}

void Vector3::SetZ(float _z)
{
	this->m_z = _z;
}

Vector3 Vector3::Zero()
{
	static Vector3 zero(0.0f, 0.0f, 0.0f);
	return zero;
}
