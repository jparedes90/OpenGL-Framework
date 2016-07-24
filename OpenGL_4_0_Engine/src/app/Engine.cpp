#include "Engine.h"
#include "SpriteBatch.h"
#include "Timer.h"
#include <iostream>
using namespace std;

Engine* Engine::m_engine = NULL;

Engine::Engine()
{
	m_graphics = NULL;
	m_input = NULL;
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

	if (m_input)
	{
		delete m_input;
		m_input = NULL;
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
	if(m_graphics)
	{
		m_graphics->Initialize();
		m_spriteBatch = m_graphics->GetSpriteBatch();
	}
	else
	{
		cout << "NO GRAPHICS CLASS INITIALIZED" << endl;
	}

	m_input = new input_manager();

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

void Engine::InitializeShaderManager()
{
	m_shaderManager = new ShaderManager();
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

	m_input->Update();

	m_graphics->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	if (m_gameComponent != NULL)
	{
		m_gameComponent->Render();
	}

	m_graphics->EndScene();
}

void Engine::InitializeCamera(Entity* cameraEntity, float flNear, float flFar)
{
	m_camera = new Camera(cameraEntity);
	m_camera->Initialize(PI / 4.0f, (float)(SCREEN_WIDTH / SCREEN_HEIGHT), flNear, flFar);
	m_camera->CreateOrthoMatrix(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, 0.0f, 1.0f);
	m_camera->SetLookAt(0, 0, -10);
	m_camera->SetPosition(0, 0, 15.0f);
	m_camera->Update(0.0f);
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

//Function: Getter for input
//PostCondition: Input object is returned
input_manager* Engine::GetInput()
{
	return m_input;
}

void Engine::OnEventCallback(UINT message, WPARAM wParam, LPARAM lParam)
{
	(void)lParam;

	switch (message)
	{
	case WM_KEYDOWN:
	{
		m_input->EventHandlerKeyDown(wParam);
	}break;
	case WM_KEYUP:
	{
		//U32 nAscii = (U32)wParam;
		m_input->EventHandlerKeyUp(wParam);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		// lParam lower 16 bits: x position
		// lParam upper 16 bits: y position
		m_input->MouseEventLDown();
		break;
	}
	case WM_LBUTTONUP:
	{
		// lParam lower 16 bits: x position
		// lParam upper 16 bits: y position
		m_input->MouseEventLUp();
		break;
	}
	case WM_RBUTTONDOWN:
	{
		m_input->MouseEventRDown();
	}break;
	case WM_RBUTTONUP:
	{
		m_input->MouseEventRUp();
	}break;
	};
}
