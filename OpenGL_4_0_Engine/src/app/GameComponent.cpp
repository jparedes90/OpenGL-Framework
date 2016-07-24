#include "GameComponent.h"

GameComponent* GameComponent::m_instance;

GameComponent::GameComponent()
{
	m_instance = this;
}

GameComponent::~GameComponent()
{
}
