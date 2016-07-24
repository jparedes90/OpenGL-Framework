#ifndef _MATH_CORE_H_
#define _MATH_CORE_H_

#define SIZE_ARRAY 4

#define PI					3.141592653589793238462643383279f
#define PIOVERTWO			1.570796326794896619231321691639f
#define TWOPI				6.283185307179586476925286766559f
#define PITWO				9.869604401089358618834490999876f
#define PIOVER180			0.01745329251994329576923690768488f
#define _180OVERPI			57.295779513082320876798154814105f

class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);

	float GetX() { return m_x; }
	float GetY() { return m_y; }

	void SetX(float _x) { m_x = _x; }
	void SetY(float _y) { m_y = _y; }
	void Set(float _x = 0.0f, float _y = 0.0f) { m_x = _x; m_y = _y; }

private:
	float m_x;
	float m_y;
};

class Vector3
{
public:
	//Vector3();
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Vector3();

	Vector3 operator + (const Vector3& vec);
	Vector3 operator += (const Vector3& vec);
	Vector3 operator - (const Vector3& vec);
	Vector3 operator -= (const Vector3& vec);
	Vector3 operator * (const Vector3& vec);
	Vector3 operator *= (const Vector3& vec);
	Vector3 operator * (const float& scalar);
	Vector3 operator *= (const float& scalar);
	Vector3 operator/(const Vector3& vec);
	Vector3 operator/(const float& scalar);
	Vector3 operator/=(const Vector3& vec);
	Vector3 operator/=(const float& scalar);

	const float& GetX()const;
	const float& GetY()const;
	const float& GetZ()const;

	void Set(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	float Length()const;
	float LengthSqr()const;
	float Dot(const Vector3& vec)const;
	void Normalize();
	static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);
	static Vector3 Zero();

private:
	float m_x{ 0.0f };
	float m_y{ 0.0f };
	float m_z{ 0.0f };
};

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	Matrix4x4 operator *(const Matrix4x4 &mat);
	Matrix4x4 operator *(const float value);
	Matrix4x4 operator *=(const Matrix4x4 &mat);
	Matrix4x4 operator *=(const float value);
	Matrix4x4 operator +(const Matrix4x4 &mat);
	Matrix4x4 operator +(const float value);
	Matrix4x4 operator +=(const Matrix4x4 &mat);
	Matrix4x4 operator +=(const float value);
	Matrix4x4 operator -(const Matrix4x4 &mat);
	Matrix4x4 operator -=(const Matrix4x4 &mat);
	Matrix4x4 operator -(const float value);
	Matrix4x4 operator -=(const float value);
	Vector3 operator *(const Vector3& v);

	float Get(int row, int col);
	void Set(int row, int col, float value);
	void SetIdentity();
	void SetTranspose();

	void BuildRotationAboutAxis(const Vector3& pAxis, float pAngle);
	void BuildRotationX(float pAngle);
	void BuildRotationY(float pAngle);
	void BuildRotationZ(float pAngle);
	void BuildTranslation(float x, float y, float z);
	void BuildTranslation(const Vector3& pTranslation);
	void BuildScale(float x, float y, float z);

	void transform(Vector3 &oPoint);

	float* AsArray();

private:
	float m_matrix[SIZE_ARRAY][SIZE_ARRAY];
};

#endif
