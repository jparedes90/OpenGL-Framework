#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include "GameComponent.h"

class GameWorld : public GameComponent
{
public:
	GameWorld();
	~GameWorld();

	void Initialize()override;
	void Update(float dt)override;
	void Render()override;
	void Release()override;

private:

};

#endif