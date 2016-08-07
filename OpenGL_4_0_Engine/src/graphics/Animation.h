//Date: 5/13/13

#ifndef ANIMATED_ENTITY_H
#define ANIMATED_ENTITY_H

#include "graphics/TextureLoader.h"
#include "RecTangle.h"
#include "SpriteBatch.h"

class Animation
{
public:
	Animation();
	~Animation();

	void Initialize(const char* pFilename, const char* pAnimationName, float pAnimationSpeed);
	void Initialize(const char* pFilename, const char* pAnimationName, int columnAnimations, int rowAnimations, int totalAnimations, float pAnimationSpeed);
	void Update(float dt);

	static void ChangeAnimation(Animation& pCurAnimation, Animation& pNewAnimation);

	RecTangle& GetSourceRect() { return m_sourceRect; }
	RecTangle& GetRect() { return m_rect; }
	TextureLoader* GetTexture() { return m_texture; }
	const char* getName();

	void SetCurrentFrame(float currentFrame);
	void SetActive(bool active);
	void SetIsLooping(bool loop);

private:
	RecTangle m_sourceRect;
	RecTangle m_rect;
	TextureLoader* m_texture;
	int m_frames;
	int m_frameWidth;
	int m_frameHeight;
	int m_rows;
	int m_currentRow;
	int m_columns;
	float m_animationSpeed;
	float m_currentFrame;
	float m_frameTimer;
	bool m_active;
	bool m_looping;
	char* m_name;
};

#endif