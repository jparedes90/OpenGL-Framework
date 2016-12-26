#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "../maths/MathCore.h"
#include "RecTangle.h"
#include "SystemDefs.h"

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	//Function: Initialize SpriteBatch
	//PostCondition: SpriteBatch is initialized
	void Initialize();

	//Function: Render 2D plane
	//PostCondition: 2D Plane rendered
	void Draw(RecTangle& rect);

	//Function: Render 2D plane
	//PostCondition: 2D Plane rendered
	void Draw(RecTangle& rect, Vector2 pTexs[4]);

	//Function: Render 2D plane
	//PostCondition: 2D Plane rendered
	void Draw(RecTangle& rect, Vector2 pTexs[4], float pScale);

	//Function: Render 2D plane
	//PostCondition: 2D Plane rendered
	void Draw(RecTangle& rect, float pScale);

	//Function: Renders a 2D plane
	//PostCondition: 2D Plane rendered
	void Draw(RecTangle& rect, RecTangle& sourceRect);

private:
	U32 m_vertexBufferID;
	U32 m_texBufferID;
	U32 m_indexBufferID;
	U32 m_vertexArrayID;
	int m_indicesCount;

	U32 m_indices[6];
	Vector3 m_verts[4];
	Vector2 m_texs[4];
};

#endif
