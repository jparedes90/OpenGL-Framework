#include "GameWorld.h"
#include "Engine.h"

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::Initialize()
{
}

void GameWorld::Update(float dt)
{
	(void)dt;
}

void GameWorld::Render()
{
	RecTangle r(0.0f, 0.0f, 2.0f, 2.0f);

	Matrix4x4 world, view, proj;

	ShaderManager::GetInstance()->GetShader("color")->BeginShader();
	ShaderManager::GetInstance()->GetShader("color")->SetShaderMatrixParameter("worldMatrix", world.AsArray());
	ShaderManager::GetInstance()->GetShader("color")->SetShaderMatrixParameter("viewMatrix", view.AsArray());
	ShaderManager::GetInstance()->GetShader("color")->SetShaderMatrixParameter("projectionMatrix", proj.AsArray());
	Engine::GetEngine()->GetGraphics()->GetSpriteBatch()->Draw(r);
	ShaderManager::GetInstance()->GetShader("color")->EndShader();
}

void GameWorld::Release()
{
}