#include "Graphics.h"
#include <assert.h>

Graphics::Graphics()
{
	m_ogl = NULL;
	m_spriteBatch = NULL;
}

Graphics::~Graphics()
{
}

//Function: Release memory
//PostCondition: Memory is released
void Graphics::Release()
{
	if(m_ogl)
	{
		delete m_ogl;
		m_ogl = NULL;
	}

	if(m_spriteBatch)
	{
		delete m_spriteBatch;
		m_spriteBatch = NULL;
	}
}

//Function: Initialize OpenGL and Extensions
//PostCondition: OpenGL and Extensions Initialized
bool Graphics::InitializeOGL(HWND pHWND)
{
	if(!m_ogl)
	{
		m_ogl = new OGL();
	}
	
	m_ogl->SetHWND(pHWND);

	if(!m_ogl->InitializeExtensions())
	{
		return false;
	}
	return true;
}

//Function: Initialize Graphics
//PostCondition: Graphics is initialized
void Graphics::Initialize()
{
	m_spriteBatch = new SpriteBatch();
	m_spriteBatch->Initialize();
}

//Function: Begins the scene
//PostCondition: Scene has begun
void Graphics::BeginScene(float r, float g, float b, float a)
{
	m_ogl->BeginScene(r, g, b, a);
}

//Function: End the scene
//PostCondition: Scene ends
void Graphics::EndScene()
{
	m_ogl->EndScene();
}

//Function: Clear the screen
//PostCondition: Clear the screen
void Graphics::ClearScreen(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
