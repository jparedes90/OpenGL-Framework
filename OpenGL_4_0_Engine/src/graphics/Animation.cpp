//Date: 5/13/13
#include "Animation.h"
#include "../managers/TextureManager.h"
#include <assert.h>

Animation::Animation()
{}

Animation::~Animation()
{}

void Animation::Initialize(const char* pFilename, const char* pAnimationName, float pAnimationSpeed)
{
	m_texture = TextureManager::GetTexture(pFilename);
	assert(m_texture);

	m_name = new char[strlen(pAnimationName)+1];
	memcpy(m_name, pAnimationName, strlen(pAnimationName)+1);

	m_frameWidth = m_texture->GetHeight();
	m_frameHeight = m_texture->GetHeight();
	m_frames = m_texture->GetWidth()/m_texture->GetHeight();
	m_currentFrame = 0.0f;
	m_frameTimer = 0.0f;
	m_animationSpeed = pAnimationSpeed;

	if (m_frames == 0 || m_frames == 1)
	{
		m_sourceRect = RecTangle(0.0f, 0.0f, (float)m_texture->GetWidth(), (float)m_frameHeight);
		m_rect = RecTangle(0.0f, 0.0f, (float)m_texture->GetWidth(), (float)m_frameHeight);
	}
	else
	{
		m_sourceRect = RecTangle(0.0f, 0.0f, (float)m_frameWidth, (float)m_frameHeight);
		m_rect = RecTangle(0.0f, 0.0f, (float)m_texture->GetWidth(), (float)m_frameHeight);
	}
}

void Animation::Initialize(const char* pFilename, const char* pAnimationName, int columnAnimations, int rowAnimations, int totalAnimations, float pAnimationSpeed)
{
	m_texture = TextureManager::GetTexture(pFilename);
	assert(m_texture);

	m_name = new char[strlen(pAnimationName)+1];
	memcpy(m_name, pAnimationName, strlen(pAnimationName)+1);

	m_frameWidth = m_texture->GetWidth()/columnAnimations;
	m_frameHeight = m_texture->GetHeight()/rowAnimations;
	m_frames = totalAnimations;
	m_currentFrame = 0.0f;
	m_currentRow = 0;
	m_frameTimer = 0.0f;
	m_animationSpeed = pAnimationSpeed;

	m_columns = columnAnimations;
	m_rows = rowAnimations;

	if (m_frames == 0 || m_frames == 1)
	{
		m_sourceRect = RecTangle(0.0f, 0.0f, (float)m_texture->GetWidth(), (float)m_frameHeight);
		m_rect = RecTangle(0.0f, 0.0f, (float)m_texture->GetWidth(), (float)m_frameHeight);
	}
	else
	{
		m_sourceRect = RecTangle(0.0f, 0.0f, (float)m_frameWidth, (float)m_frameHeight);
		m_rect = RecTangle(0.0f, 0.0f, (float)m_texture->GetWidth(), (float)m_frameHeight);
	}
}

void Animation::Update(float dt)
{
	if(!m_active)
	{
		return;
	}

	m_frameTimer += m_animationSpeed * dt;

	if(m_frameTimer > 24.0f)
	{
		m_currentFrame++;

		if(m_currentFrame >= m_columns)
		{
			if((m_currentRow + 1) < m_rows)
			{
				m_currentFrame = 0;
				m_currentRow++;
			}
		}

		if(m_currentFrame >= m_frames)
		{
			if(m_looping)
			{
				m_currentFrame = 0;
			}
			else
			{
				m_active = false;
			}
		}

		m_frameTimer = 0.0f;
	}

	m_sourceRect.Set(m_currentFrame * m_frameWidth, (float)m_currentRow * m_frameHeight);
}

void Animation::ChangeAnimation(Animation& pCurAnimation, Animation& pNewAnimation)
{
	if(&pCurAnimation == &pNewAnimation)
	{
		return;
	}

	pCurAnimation = pNewAnimation;
}

const char* Animation::getName()
{
	return m_name;
}

void Animation::SetCurrentFrame(float currentFrame)
{
	m_currentFrame = currentFrame;
}

void Animation::SetActive(bool active)
{
	m_active = active;
}

void Animation::SetIsLooping(bool loop)
{
	m_looping = loop;
}
