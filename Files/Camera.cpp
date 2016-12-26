#include "Camera.h"
//#include "Camera.h"
#include <Windows.h>
#include <iostream>
#include "../app/Engine.h"

using namespace std;

Camera::Camera(Entity* entity) : Component(entity)
{}

Camera::~Camera()
{}

void Camera::Initialize(float fov, float aspect, float pNear, float pFar)
{
	Component::Initialize();

	float f = 1.0f / tanf(fov / 2.0f);

	// Transposed version of D3DXMatrixPerspectiveFovRH
	m_projectionMatrix.Set(0, 0, f / aspect);
	m_projectionMatrix.Set(1, 1, f);
	m_projectionMatrix.Set(2, 2, (-pNear - pFar) / ( pNear - pFar ));
	m_projectionMatrix.Set(2, 3, (2.0f * pNear * pFar ) / (pNear - pFar ));
	m_projectionMatrix.Set(3, 2, 1.0f);
	//m_projectionMatrix.Set(3, 3, 0.0f);
	
	m_yawRotation.BuildRotationAboutAxis(Vector3(0, 1, 0), 0.0f);
	m_pitchRotation.BuildRotationAboutAxis(Vector3(1, 0, 0), 0.0f);
}

void Camera::CreateOrthoMatrix(float left, float right, float top, float bottom, float nearZ, float farZ)
{
	m_orthoMatrix.Set(0, 0, 2/(right-left));
	m_orthoMatrix.Set(1, 1, 2/(top - bottom));
	m_orthoMatrix.Set(2, 2, -2/(farZ - nearZ));
	m_orthoMatrix.Set(0, 3,-((right+left)/(right-left)));
	m_orthoMatrix.Set(1, 3, -((top+bottom)/(top - bottom)));
	m_orthoMatrix.Set(2, 3, -((farZ+nearZ)/(farZ-nearZ)));
}

void Camera::Update(float dt)
{
	Component::Update(dt);

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	Vector3 upVector(0, 1, 0);
	Vector3 rightVector(1, 0, 0);
	Vector3 lookAtVector = m_lookAt - m_position;

	lookAtVector.Normalize();

	m_pitchRotation.transform(lookAtVector);
	m_yawRotation.transform(lookAtVector);

	lookAtVector.Normalize();

	rightVector = Vector3::Cross(lookAtVector, upVector);
	rightVector.Normalize();

	upVector = Vector3::Cross(rightVector, lookAtVector);
	upVector.Normalize();

	m_viewMatrix.Set(0, 0, rightVector.GetX());
	m_viewMatrix.Set(0, 1, rightVector.GetY());
	m_viewMatrix.Set(0, 2, rightVector.GetZ());

	m_viewMatrix.Set(1, 0, upVector.GetX());
	m_viewMatrix.Set(1, 1, upVector.GetY());
	m_viewMatrix.Set(1, 2, upVector.GetZ());

	m_viewMatrix.Set(2, 0, lookAtVector.GetX()); 
	m_viewMatrix.Set(2, 1, lookAtVector.GetY());
	m_viewMatrix.Set(2, 2, lookAtVector.GetZ());

	m_viewMatrix.Set(0, 3, -m_position.Dot(rightVector));
	m_viewMatrix.Set(1, 3, -m_position.Dot(upVector));
	m_viewMatrix.Set(2, 3, -m_position.Dot(lookAtVector));
}

Matrix4x4 Camera::GetRotationMatrix()
{
	Matrix4x4 rot;
	
	rot.Set(0, 0, m_viewMatrix.Get(0, 0));
	rot.Set(0, 1, m_viewMatrix.Get(0, 1));
	rot.Set(0, 2, m_viewMatrix.Get(0, 2));

	rot.Set(1, 0, m_viewMatrix.Get(1, 0));
	rot.Set(1, 1, m_viewMatrix.Get(1, 1));
	rot.Set(1, 2, m_viewMatrix.Get(1, 2));

	rot.Set(2, 0, m_viewMatrix.Get(2, 0));
	rot.Set(2, 1, m_viewMatrix.Get(2, 1));
	rot.Set(2, 2, m_viewMatrix.Get(2, 2));

	return rot;
}

void Camera::Reset()
{
	m_yawRotation.SetIdentity();
	m_pitchRotation.SetIdentity();
	m_rotation.Zero();
}
