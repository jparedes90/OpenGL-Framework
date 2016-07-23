#ifndef ENGINE_H
#define ENGINE_H

#include "Graphics.h"
#include "GameComponent.h"
#include "ShaderManager.h"
#include "TextureManager.h"

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

private:
	Engine();

	static Engine* m_engine;

	GameComponent* m_gameComponent;
	Graphics* m_graphics;
	class SpriteBatch* m_spriteBatch;
	ShaderManager* m_shaderManager;
	TextureManager* m_textureManager;
};

#endif