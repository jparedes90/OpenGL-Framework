#include "FrameWork.h"
#include "SystemDefs.h"
#include "Timer.h"
#include <assert.h>
#include <iostream>

using namespace std;

LRESULT CALLBACK WndProc(HWND pHWND, UINT pMessage, WPARAM wParam, LPARAM lParam);

FrameWork::FrameWork(void)
{
	m_projectName = "";
}

FrameWork::~FrameWork(void)
{
	//if the window is fullscreen make sure to disable it before deleting the window
	if(FULL_SCREEN == true)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	Engine::GetEngine()->Release();

	UnregisterClass(m_projectName.c_str(), m_hInstance);
	m_hInstance = NULL;
}

//Function: Initialize our framework
//PostCondition: Framework is initialized
void FrameWork::Initialize(GameComponent* pGameComponent, string projectName)
{
	m_engine = Engine::GetEngine();
	m_projectName = projectName;

	m_iWindowWidth = SCREEN_WIDTH;
	m_iWindowHeight = SCREEN_HEIGHT;

	if (!CreateOpenGLWindow((char*)m_projectName.c_str(), WIND_POSX, WIND_POSY, m_iWindowWidth, m_iWindowHeight))
	{
		return;
	}

	m_engine->Initialize(pGameComponent);

	hwnd = Engine::GetEngine()->GetGraphics()->GetOpenGL()->GetHWND();
}

//Function: Runs and updates the framework
//PostCondition: Framework is updated
void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//update loop
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//update timer
			Timer::Update();

			//run the engine
			m_engine->Run();
		}
	}
}

//Function: Create the OpenGL window
//PostCondition: OpenGL window is created
bool FrameWork::CreateOpenGLWindow(char* pTitle, int x, int y, int width, int height)
{
	//HWND hwnd = 0;

	WNDCLASSEX wc;

	m_hInstance = GetModuleHandle(NULL);

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = pTitle;
	wc.cbSize        = sizeof(WNDCLASSEX);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClass() failed: "
			"Cannot register window class. ", "Error", MB_OK);
		return false;
	}


	// Create a temporary window for the OpenGL extension setup.
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, pTitle, pTitle, WS_POPUP,
				0, 0, 640, 480, NULL, NULL, m_hInstance, NULL);
	if(hwnd == NULL)
	{
		MessageBox(NULL, "CreateWindow() failed: Cannot create a window.", "Error", MB_OK);

		return false;
	}

	// Don't show the window.
	ShowWindow(hwnd, SW_HIDE);

	//initialize graphics and opengl extensions
	if(!m_engine->InitializeGraphics(hwnd))
	{
		MessageBox(hwnd, "Could not initialize the OpenGL extensions.", "Error", MB_OK);
		m_engine->Release();
		m_engine = NULL;
		PostQuitMessage(0);
		DestroyWindow( hwnd );

		return false;
	}

	// Release the temporary window now that the extensions have been initialized.
	DestroyWindow(hwnd);
	hwnd = NULL;

	//calculate entire client-area rectangle by taking into account window styles
	int nStyle = WS_OVERLAPPED|WS_SYSMENU|WS_VISIBLE|WS_CAPTION|WS_MINIMIZEBOX;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	DEVMODE dmScreenSettings;

	if(FULL_SCREEN == true)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		// If windowed then set it to a desired resolution.
		screenWidth  = width;
		screenHeight = height;

		// Place the window in the middle of the screen.
		//x = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		//y = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, pTitle, pTitle, nStyle,
				x, y, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);
	if(hwnd == NULL)
	{
		MessageBox(NULL, "CreateWindow() failed: Cannot create a window.", "Error", MB_OK);

		m_engine->Release();
		m_engine = NULL;
		PostQuitMessage(0);

		return false;
	}

	m_engine->GetGraphics()->GetOpenGL()->SetHWND(hwnd);

	if(!m_engine->GetGraphics()->GetOpenGL()->InitializeOGL(VSYNC_ENABLED))
	{
		MessageBox(hwnd, "Could not initialize OpenGL, check if video card supports OpenGL 4.0.", "Error", MB_OK);
		m_engine->Release();
		m_engine = NULL;
		PostQuitMessage(0);
		UnregisterClass(m_projectName.c_str(), m_hInstance);
		m_hInstance = NULL;
		DestroyWindow( hwnd );

		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return true;
}

static bool ignorOnce = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	Engine::GetEngine()->OnEventCallback(message, wParam, lParam);

	switch ( message ) 
	{
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
		{
			PostQuitMessage(0);
			DestroyWindow( hWnd );
		}
		else 
		{
			//U32 nAscii = (U32)wParam;
			//input->EventHandlerKeyDown(wParam);
		}
		break;
	case WM_KEYUP:
		{
			//U32 nAscii = (U32)wParam;
			//input->EventHandlerKeyUp(wParam);
		}
		break;
	case WM_MOUSEMOVE:
		{
			// lParam lower 16 bits: x position
			// lParam upper 16 bits: y position

			break;
		}
	case WM_LBUTTONDOWN:
		{
			// lParam lower 16 bits: x position
			// lParam upper 16 bits: y position
			//input->MouseEventLDown();
			break;
		}
	case WM_LBUTTONUP:
		{
			// lParam lower 16 bits: x position
			// lParam upper 16 bits: y position
			//input->MouseEventLUp();
			break;
		}	
	case WM_RBUTTONDOWN:
		{
			//input->MouseEventRDown();
		}break;
	case WM_RBUTTONUP:
		{
			//input->MouseEventRUp();
		}break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		//PostQuitMessage(0);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow( hWnd );
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}
