#include "SpriteBatch.h"
#include <GL\glew.h>
#include <assert.h>
using namespace std;

SpriteBatch::SpriteBatch()
{
	m_vertexBufferID = 0;
	m_indexBufferID = 0;
	m_vertexArrayID = 0;
	m_texBufferID = 0;
}

SpriteBatch::~SpriteBatch()
{
	if(m_vertexBufferID)
	{
		glDeleteBuffers(1, &m_vertexBufferID);
	}
	if(m_texBufferID)
	{
		glDeleteBuffers(1, &m_texBufferID);
	}
	if(m_indexBufferID)
	{
		glDeleteBuffers(1, &m_indexBufferID);
	}
	if(m_vertexArrayID)
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_vertexArrayID);
	}
}

//Function: Initialize SpriteBatch
//PostCondition: SpriteBatch is initialized
void SpriteBatch::Initialize()
{
	glGenVertexArrays(1, &m_vertexArrayID);
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_texBufferID);
	glGenBuffers(1, &m_indexBufferID);
	glBindVertexArray(0);

	m_indices[0] = 0;
	m_indices[1] = 2;
	m_indices[2] = 1;
	m_indices[3] = 1;
	m_indices[4] = 2;
	m_indices[5] = 3;

	m_indicesCount = 6;
}

//Function: Render 2D plane
//PostCondition: 2D Plane rendered
void SpriteBatch::Draw(RecTangle& rect)
{
	float width = rect.GetWidth();
	float height = rect.GetHeight();

	float left = -(width/2.0f) + rect.GetLeft();
	float right = left + width;
	float top = -(height/2.0f) + rect.GetTop();
	float bottom = top + height;

	m_verts[0] = Vector3(left, top, 0.0f);
	m_texs[0] = Vector2(0.0f, 0.0f);

	m_verts[1] = Vector3(right, top, 0.0f);
	m_texs[1] = Vector2(1.0f, 0.0f);

	m_verts[2] = Vector3(left, bottom, 0.0f);
	m_texs[2] = Vector2(0.0f, 1.0f);

	m_verts[3] = Vector3(right, bottom, 0.0f);
	m_texs[3] = Vector2(1.0f, 1.0f);

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector3), m_verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), m_texs, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(U32), m_indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

//Function: Render 2D plane
//PostCondition: 2D Plane rendered
void SpriteBatch::Draw(RecTangle& rect, RecTangle& sourceRect)
{
	float width = sourceRect.GetWidth();
	float height = sourceRect.GetHeight();

	float left = -(width/2.0f) + rect.GetLeft();
	float right = left + width;
	float top = -(height/2.0f) + rect.GetTop();
	float bottom = top + height;

	width = rect.GetWidth();
	height = rect.GetHeight();

	float u1 = sourceRect.GetLeft() / width;
	float u2 = sourceRect.GetRight() / width;
	float v1 = sourceRect.GetTop() / height;
	float v2 = sourceRect.GetBottom() / height;

	m_verts[0] = Vector3(left, top, 0.0f);
	m_texs[0] = Vector2(u1, v1);

	m_verts[1] = Vector3(right, top, 0.0f);
	m_texs[1] = Vector2(u2, v1);

	m_verts[2] = Vector3(left, bottom, 0.0f);
	m_texs[2] = Vector2(u1, v2);

	m_verts[3] = Vector3(right, bottom, 0.0f);
	m_texs[3] = Vector2(u2, v2);

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector3), m_verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), m_texs, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(U32), m_indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

//Function: Render 2D plane
//PostCondition: 2D Plane rendered
void SpriteBatch::Draw(RecTangle& rect, float pScale)
{
	float width = rect.GetWidth();
	float height = rect.GetHeight();

	float left = -(width/2.0f * pScale) + rect.GetLeft();
	float right = left + width * pScale;
	float top = -(height/2.0f * pScale) + rect.GetTop();
	float bottom = top + height * pScale;

	m_verts[0] = Vector3(left, top, 0.0f);
	m_texs[0] = Vector2(0.0f, 0.0f);

	m_verts[1] = Vector3(right, top, 0.0f);
	m_texs[1] = Vector2(1.0f, 0.0f);

	m_verts[2] = Vector3(left, bottom, 0.0f);
	m_texs[2] = Vector2(0.0f, 1.0f);

	m_verts[3] = Vector3(right, bottom, 0.0f);
	m_texs[3] = Vector2(1.0f, 1.0f);

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector3), m_verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), m_texs, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(U32), m_indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

//Function: Render 2D plane
//PostCondition: 2D Plane rendered
void SpriteBatch::Draw(RecTangle& rect, Vector2 pTexs[4])
{
	float width = rect.GetWidth();
	float height = rect.GetHeight();

	float left = -(width/2.0f) + rect.GetLeft();
	float right = left + width;
	float top = -(height/2.0f) + rect.GetTop();
	float bottom = top + height;

	m_verts[0] = Vector3(left, top, 0.0f);
	m_verts[1] = Vector3(right, top, 0.0f);
	m_verts[2] = Vector3(left, bottom, 0.0f);
	m_verts[3] = Vector3(right, bottom, 0.0f);

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector3), m_verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), pTexs, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(U32), m_indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

//Function: Render 2D plane
//PostCondition: 2D Plane rendered
void SpriteBatch::Draw(RecTangle& rect, Vector2 pTexs[4], float pScale)
{
	float width = rect.GetWidth();
	float height = rect.GetHeight();

	float left = -(width/2.0f * pScale) + rect.GetLeft();
	float right = left + width * pScale;
	float top = -(height/2.0f * pScale) + rect.GetTop();
	float bottom = top + height * pScale;

	m_verts[0] = Vector3(left, top, 0.0f);
	m_verts[1] = Vector3(right, top, 0.0f);
	m_verts[2] = Vector3(left, bottom, 0.0f);
	m_verts[3] = Vector3(right, bottom, 0.0f);

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector3), m_verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), pTexs, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(U32), m_indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
