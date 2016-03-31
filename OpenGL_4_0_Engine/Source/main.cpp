#include "Framework.h"
#include "GameWorld.h"

int main()
{
	FrameWork framework;
	framework.Initialize(new GameWorld(), "OpenGL 4.0 Engine");
	framework.Run();

	return 0;
}