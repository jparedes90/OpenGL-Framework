#ifndef GRAPHICS_H
#define GRAPHICS_H

static bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;

#include "OGL.h"
#include "SpriteBatch.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	//Function: Initialize OpenGL and Extensions
	//PostCondition: OpenGL and Extensions Initialized
	bool InitializeOGL(HWND pHWND);

	//Function: Initialize Graphics
	//PostCondition: Graphics is initialized
	void Initialize();

	//Function: Clear the screen
	//PostCondition: Clear the screen
	void ClearScreen(float r, float g, float b, float a);

	//Function: Begins the scene
	//PostCondition: Scene has begun
	void BeginScene(float r, float g, float b, float a);

	//Function: End the scene
	//PostCondition: Scene ends
	void EndScene();
	
	//Function: Getter for OpenGL
	//PostCondition: OpenGL object is returned
	OGL* GetOpenGL() { return m_ogl; }

	//Function: Getter for SpriteBatch
	//PostCondition: SpriteBatch is returned
	SpriteBatch* GetSpriteBatch() { return m_spriteBatch; }

	//Function: Release memory
	//PostCondition: Memory is released
	void Release();

private:
	OGL* m_ogl;
	SpriteBatch* m_spriteBatch;
};

#endif
