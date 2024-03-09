#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
	// Controls rotation (radians/seconds)
	float mAngularSpeed;
	// Controls forward movement (units/second)
	float mForwardSpeed;
	// Newtonian physics
	// mass: a scalar that represent the quantity of matter contained in an object
	// mass is independent of gravity
	// the greater the mass of an object, the more difficult it is to change the movement of that object
	float mass;
	// Force = mass x acceleration 
	// acceleration the rate at which the velocity of an object increases
	// acceleration is force divided by mass

	// An arbitrary object in the game has a mass, and you can apply forces to that object -> you can then compute the acceleration of the object
	float sumOfForces;

	// A game needs to apply a force to an object and, from that force determine the acceleration over time
	// Once you have an object's acceleration, you can compute the change in the object's velocity
	
	// Given a velocity, you can compute the change in the object's position
	// A game only needs to compute this in terms of the discrete time steps of delta time
	float velocity;
	// You need numeric integration
	// numeric integration allows a game to update the velocity based on the acceleration and then update the position based on the velocity
	// To compute the acceleration of an object the game needs to know the mass of the object as well as the forces applied to the object

	// There are multiple forces to consider
	// Gravity is constant and should apply every frame
	// Other forces may instead be impulses, or forces that apply only for a single frame
	// Because multiple forces can act on an object simultaneously, and forces are vectors, adding up all the forces gives the total force applied to an object
	// for that frame. 
	// Dividing the sum of forces by mass yields accelration:

	// acceleration = sumOfForces / mass;

	// Then use Euler integration to compute the velocity and the position

	// (Semi-Implicit) Euler Integration
	// Update velocity
	// velocity += acceleration * deltaTime;
	// Update the position
	// position += velocity * deltaTime

};

