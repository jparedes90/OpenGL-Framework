#include "Engine.h"
#include "SpriteBatch.h"
#include "Timer.h"
#include <iostream>
using namespace std;

Engine* Engine::m_engine = NULL;

Engine::Engine()
{
	m_graphics = NULL;
	m_gameComponent = NULL;
	m_spriteBatch = NULL;
	m_shaderManager = NULL;
	m_textureManager = NULL;
}

Engine::~Engine()
{
	if(m_graphics)
	{
		m_graphics->Release();
		delete m_graphics;
		m_graphics = NULL;
	}

	if (m_shaderManager)
	{
		delete m_shaderManager;
		m_shaderManager = NULL;
	}

	if (m_textureManager)
	{
		delete m_textureManager;
		m_textureManager = NULL;
	}

	if(m_gameComponent)
	{
		m_gameComponent->Release();
		delete m_gameComponent;
		m_gameComponent = NULL;
	}
}

//Function: Singleton for Engine
//PostCondition: Singleton for Engine is returned
Engine* Engine::GetEngine()
{
	if(!m_engine)
	{
		m_engine = new Engine();
	}

	return m_engine;
}

//Function: Getter for graphics
//PostCondition: Graphics object is returned
Graphics* Engine::GetGraphics()
{
	return m_graphics;
}

//Function: Initialize graphics
//PostCondition: Graphics is initialized
bool Engine::InitializeGraphics(HWND pHWND)
{
	m_graphics = new Graphics();

	return m_graphics->InitializeOGL(pHWND);
}

//Function: Initialize Engine
//PostCondition: Engine is initialized
void Engine::Initialize(GameComponent* pComponent)
{
	m_shaderManager = new ShaderManager();

	if(m_graphics)
	{
		m_graphics->Initialize();
		m_spriteBatch = m_graphics->GetSpriteBatch();
	}
	else
	{
		cout << "NO GRAPHICS CLASS INITIALIZED" << endl;
	}

	//m_input = new input_manager();

	m_gameComponent = pComponent;
	if(m_gameComponent != NULL)
	{
		m_gameComponent->Initialize();
	}
	else
	{
		cout << "NO GAME COMPONENT" << endl;
	}
}

//Function: Allocate Texture Manager
//PostCondition: Texture Manager allocated
void Engine::InitializeTextureManager()
{
	m_textureManager = new TextureManager();
}

//Function: Updates and Renders the Engine
//PostCondition: Engine is updated and rendered
void Engine::Run()
{
	float dt = Timer::GetDeltaTime();
	if(m_gameComponent != NULL)
	{
		m_gameComponent->Update(dt);
	}

	m_graphics->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	if (m_gameComponent != NULL)
	{
		m_gameComponent->Render();
	}

	m_graphics->EndScene();
}

//Function: Release memory
//PostCondition: Memory is released
void Engine::Release()
{	
	if(m_engine)
	{
		delete m_engine;
		m_engine = NULL;
	}
}