#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define WIN32_LEAN_AND_MEAN

#include "../graphics/OGL.h"
#include "Engine.h"
#include <string>

class FrameWork
{
public:
	FrameWork(void);
	~FrameWork(void);

	//Function: Initialize our framework
	//PostCondition: Framework is initialized
	void Initialize(GameComponent* pGameComponent, std::string projectName);

	//Function: Runs and updates the framework
	//PostCondition: Framework is updated
	void Run();

	int							GetWindowWidth() { return (int)m_iWindowWidth; };
	int							GetWindowHeight() { return (int)m_iWindowHeight; };

private:
	//Function: Create the OpenGL window
	//PostCondition: OpenGL window is created
	bool CreateOpenGLWindow(char* pTitle, int x, int y, int width, int height);

	HINSTANCE m_hInstance;
	Engine* m_engine;

	std::string m_projectName;
	size_t						m_iWindowWidth;
	size_t						m_iWindowHeight;
	HWND hwnd;
};

#endif
