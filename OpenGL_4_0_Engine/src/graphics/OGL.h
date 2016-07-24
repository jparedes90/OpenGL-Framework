#ifndef OGL_H
#define OGL_H

//#include <Windows.h>
#include <GL\glew.h>
#include <GL\wglew.h>

/////////////////
////// DEFINES //
/////////////////
#define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092

////The following are the typedefs that we need to access the OpenGL 4.0 functionality
////////////////
//// TYPEDEFS //
////////////////
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

class OGL
{
public:
	OGL();
	~OGL();

	//Function: Initialize OpenGL Extensions
	//PostCondition: OpenGL Extensions initialized
	bool InitializeExtensions();

	//Function: Initialize OpenGL
	//PostCondition: OpenGL initialized
	bool InitializeOGL(bool vSync);

	//Function: Begin Scene
	//PostCondition: Scene has begun
	void BeginScene(float red, float green, float blue, float alpha);

	//Function: End Scene
	//PostCondition: Scene has ended
	void EndScene();

	//Function: Gets name of GPU
	//PostCondition: GPU name returned
	void GetVideoCardInfo(char* pInfo);

	//Function: Getter for HWND
	//PostCondition: HWND returned
	HWND GetHWND() { return m_hwnd; }

	//Function: Release Memory
	//PostCondition: Memory is released
	void Release();

	//Function: Sets HWND
	//PostCondition: HWND is set
	void SetHWND(HWND pHWND) { m_hwnd = pHWND; }

private:
	//Function: Load extensions
	//PostCondition: Extensions loaded
	bool LoadExtensionList();

	HDC m_deviceContext;
	HGLRC m_renderingContext;
	HWND m_hwnd;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

	char m_videoCardDescription[128];
};

#endif
