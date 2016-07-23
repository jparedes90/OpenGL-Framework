#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "GameComponent.h"

class GameScene :
	public GameComponent
{
public:
	GameScene();
	virtual ~GameScene();

	//Function: Initialize GameComponent
	//PostCondition: GameComponent Initialize
	void Initialize()override;

	//Function: Update GameComponent
	//PostCondition: GameComponent is updated
	void Update(float dt)override;

	void Render()override;

	//Function: Release Memory
	//PostCondition: Memory released
	void Release()override;
};

#endif