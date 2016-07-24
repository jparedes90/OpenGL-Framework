#include "OGL.h"
#include <iostream>
using namespace std;

OGL::OGL()
{
	m_deviceContext = 0;
	m_renderingContext = 0;
}

OGL::~OGL()
{
}

//Function: Initialize OpenGL Extensions
//PostCondition: OpenGL Extensions initialized
bool OGL::InitializeExtensions()
{
	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error = 0;
	HGLRC renderContext;
	bool result = false;

	//get the device content for this window
	deviceContext = GetDC(m_hwnd);
	if(!deviceContext)
	{
		return false;
	}

	//set temporary default pixel format
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if(error != 1)
	{
		return false;
	}

	//create a temporary rendering context
	renderContext = wglCreateContext(deviceContext);
	if(!renderContext)
	{
		return false;
	}

	//set temporary rendering context as the current rendering context for this window
	error = wglMakeCurrent(deviceContext, renderContext);
	if(error != 1)
	{
		return false;
	}

	//Initialize OpenGL extensions needed
	result = LoadExtensionList();
	if(!result)
	{
		return false;
	}

	//release variables
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;
	ReleaseDC(m_hwnd, deviceContext);
	deviceContext = 0;

	return true;
}

//Function: Initialize OpenGL
//PostCondition: OpenGL initialized
bool OGL::InitializeOGL(bool vSync)
{
	cout << "Initializing OpenGL" << endl;

	//int attributeListInt[19];
	int pixelFormat;
	//unsigned int formatCount;
	int result = 0;
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor={ 
												sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd 
												1, // version number 
												PFD_DRAW_TO_WINDOW | // support window 
												PFD_SUPPORT_OPENGL | // support OpenGL 
												PFD_DOUBLEBUFFER, // double buffered 
												PFD_TYPE_RGBA, // RGBA type 
												24, // 24-bit color depth 
												0, 0, 0, 0, 0, 0, // color bits ignored 
												0, // no alpha buffer 
												0, // shift bit ignored 
												0, // no accumulation buffer 
												0, 0, 0, 0, // accum bits ignored 
												32, // 32-bit z-buffer 
												0, // no stencil buffer 
												0, // no auxiliary buffer 
												PFD_MAIN_PLANE, // main layer 
												0, // reserved 
												0, 0, 0 // layer masks ignored 
												}; 

	int attributeList[5];
	char* vendorString, *rendererString;

	//get the device
	m_deviceContext = GetDC(m_hwnd);
	if(!m_deviceContext)
	{
		return false;
	}

	//set OpenGL rendering
	/*attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	//Support for rendering to a window
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	// Support for hardware acceleration.
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

	// Support for 24bit color.
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;

	// Support for 24 bit depth buffer.
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	// Support for double buffer.
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	// Support for swapping front and back buffer.
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

	// Support for the RGBA pixel type.
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;

	// Support for a 8 bit stencil buffer.
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	// Null terminate the attribute list.
	attributeListInt[18] = 0;*/

	//Query for a pixel format that fist the attribute we want
	
	pixelFormat = ChoosePixelFormat(m_deviceContext, &pixelFormatDescriptor);
	if(pixelFormat == 0)
	{
		return false;
	}

	//if the video card can handle our desired pixel format
	result = SetPixelFormat(m_deviceContext, pixelFormat, &pixelFormatDescriptor);
	if(result != 1)
	{
		return false;
	}

	//make temporary context to initialize opengl extension wrangler
	HGLRC tempOpenGLContext = wglCreateContext(m_deviceContext); // Create an OpenGL 2.1 context for our device context
	wglMakeCurrent(m_deviceContext, tempOpenGLContext); // Make the OpenGL 2.1 context current and active

	if(glewInit() != GLEW_OK)
	{
		return false;
	}
	
	//Set the 4.0 version of OpenGL in the attribute list
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;
	attributeList[4] = 0;

	//create a OpenGL 4.0 rendering context
	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, 0, attributeList);
	
	if(m_renderingContext != NULL)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempOpenGLContext);

		//Set the rendering context active
		result = wglMakeCurrent(m_deviceContext, m_renderingContext);
		if(result != 1)
		{
			return false;
		}
	}

	//set the depth buffer to be entirely cleared to 1.0 values
	//glClearDepth(1.0f);
	//glEnable(GL_DEPTH_TEST);
	//set the polygon winding to front facing for LH sytem
	//glFrontFace(GL_CW);

	//Enable back face culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	vendorString = (char*)glGetString(GL_VENDOR);
	rendererString = (char*)glGetString(GL_RENDERER);

	//store info
	strcpy_s(m_videoCardDescription, vendorString);
	strcat_s(m_videoCardDescription, "-");
	strcat_s(m_videoCardDescription, rendererString);

	if(vSync)
	{
		result = wglSwapIntervalEXT(1);
	}
	else
	{
		result = wglSwapIntervalEXT(0);
	}

	//check if vsync was set correctly
	if(result != 1)
	{
		cout << "Error setting VSync" << endl;
		return false;
	}

	int glVersion[2] = {-1,-1};
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]); // Get back the OpenGL MAJOR version we are using
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]); // Get back the OpenGL MAJOR version we are using
	
	cout << "Initializing OpenGL successful!" << endl;
	cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << endl;
	cout << "GPU: " << m_videoCardDescription << endl;

	return true;
}

//Function: Release Memory
//PostCondition: Memory is released
void OGL::Release()
{
	if(m_renderingContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = 0;
	}

	if(m_deviceContext)
	{
		ReleaseDC(m_hwnd, m_deviceContext);
		m_deviceContext = 0;
	}
}

//Function: Begin Scene
//PostCondition: Scene has begun
void OGL::BeginScene(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Function: End Scene
//PostCondition: Scene has ended
void OGL::EndScene()
{
	glFlush();
	//Present the back buffer to the screen since rendering is complete
	SwapBuffers(m_deviceContext);
	glFinish();
}

//Function: Load extensions
//PostCondition: Extensions loaded
bool OGL::LoadExtensionList()
{
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if(!wglCreateContextAttribsARB)
	{
		return false;
	}

	return true;
}
