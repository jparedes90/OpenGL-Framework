#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

class GameComponent
{
public:
	GameComponent();
	virtual ~GameComponent();

	//Function: Initialize GameComponent
	//PostCondition: GameComponent Initialize
	virtual void Initialize() = 0;

	//Function: Update GameComponent
	//PostCondition: GameComponent is updated
	virtual void Update(float dt) = 0;

	virtual void Render() = 0;

	//Function: Release Memory
	//PostCondition: Memory released
	virtual void Release()=0;

private:
	static GameComponent* m_instance;
};

#endif