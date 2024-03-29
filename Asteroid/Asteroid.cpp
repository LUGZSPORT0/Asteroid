#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	, mCircle(nullptr)
{
	// Initialize to random position/orientation
	Vector2 randPos = Random::GetVector(Vector2::Zero,
		Vector2(1024.0f, 768.0f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	// Create a move component, and set a forward speed
	mc = new MoveComponent(this);

	mc->SetMass(1000.0f);
	mc->SetForwardSpeed(150.0f);
	force.x = mc->GetMass() * mc->GetForwardSpeed();

	mc->AddForces(force);
	// Create a circleComponent (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(32.0f);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	force.x = mc->GetMass() * mc->GetForwardSpeed();
	mc->AddForces(force);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}