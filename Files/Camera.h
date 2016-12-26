#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"
#include "../maths/MathCore.h"

class Entity;

class Camera : public Component
{
public:
	Camera(Entity* entity);
	~Camera();

	virtual void Initialize(float fov, float aspect, float pNear, float pFar);
	void CreateOrthoMatrix(float left, float right, float top, float bottom, float nearZ, float farZ);
	virtual void Update(float dt);

	const Matrix4x4& GetViewMatrix()const { return m_viewMatrix; }
	const Matrix4x4& GetProjectionMatrix()const { return m_projectionMatrix; }
	const Matrix4x4& GetOrthoMatrix()const { return m_orthoMatrix; }
	Matrix4x4 GetRotationMatrix();
	const Vector3& GetPosition()const { return m_position; }
	const Vector3& GetLookAt() { return m_lookAt; }

	void SetPosition(float x, float y, float z) { m_position.Set(x, y, z); }
	void SetPosition(const Vector3& pos) { m_position = pos; }
	void SetLookAt(float x, float y, float z) { m_lookAt.Set(x, y, z); }
	void Reset();

protected:
	
	void UpdateViewMatrix();

	Matrix4x4 m_viewMatrix;
	Matrix4x4 m_projectionMatrix;
	Matrix4x4 m_orthoMatrix;
	
	Matrix4x4 m_yawRotation;
	Matrix4x4 m_pitchRotation;
	Vector3 m_position;
	Vector3 m_lookAt;
	Vector3 m_rotation;
	Vector3 m_frameRotation;
};

#endif
