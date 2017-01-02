#ifndef ENGINE_H
#define ENGINE_H

#include "../graphics/Graphics.h"
#include "GameComponent.h"
#include "../managers/ShaderManager.h"
#include "../managers/TextureManager.h"
#include "inputs\input_manager.h"
//#include "../graphics/Camera.h"

class Engine
{
public:
	~Engine();

	//Function: Initialize graphics
	//PostCondition: Graphics is initialized
	bool InitializeGraphics(HWND pHWND);

	//Function: Initialize Engine
	//PostCondition: Engine is initialized
	void Initialize(GameComponent* pComponent);

	//Function: Allocate Texture Manager
	//PostCondition: Texture Manager allocated
	void InitializeTextureManager();

	//Function: Allocate Shader Manager
	//PostCondition: Shader Manager allocated
	void InitializeShaderManager();

	//void InitializeCamera(class Entity* cameraEntity, float flNear, float flFar);

	//Function: Updates and Renders the Engine
	//PostCondition: Engine is updated and rendered
	void Run();

	//Function: Singleton for Engine
	//PostCondition: Singleton for Engine is returned
	static Engine* GetEngine();

	//Function: Getter for graphics
	//PostCondition: Graphics object is returned
	Graphics* GetGraphics();

	//Function: Release memory
	//PostCondition: Memory is released
	void Release();

	//Function: Getter for input
	//PostCondition: Input object is returned
	input_manager* GetInput();

	//const Camera* GetCamera()const { return m_camera; }

	void OnEventCallback(UINT message, WPARAM wParam, LPARAM lParam);

private:
	Engine();

	static Engine* m_engine;

	input_manager* m_input;
	GameComponent* m_gameComponent;
	Graphics* m_graphics;
	class SpriteBatch* m_spriteBatch;
	ShaderManager* m_shaderManager;
	TextureManager* m_textureManager;
	//Camera* m_camera;
};

#endif
