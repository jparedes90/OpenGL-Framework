#include "FrameWork.h"
#include "GameScene.h"

void main()
{
	FrameWork framework;
	framework.Initialize(new GameScene(), "SuperMarioGame");
	framework.Run();

	return;
}