#pragma once
#include "Actor.h"
class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();

	class CircleComponent* GetCircle() { return mCircle; }
	void UpdateActor(float deltaTime) override;
	
private:
	class CircleComponent* mCircle;
	class MoveComponent* mc;
	Vector2 force;
};

