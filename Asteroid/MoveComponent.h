#pragma once
#include "Component.h"
#include "math.h"

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
	void SetMass(float matter) { mass = matter; }
	void AddForces(Vector2 force) { sumOfForces = force; };

	float GetMass() { return mass; }
	Vector2 GetForces() { return sumOfForces; }
	void Deaccelerate(bool isDeaccelerate) { deaccelerate = isDeaccelerate; }
private:
	bool deaccelerate;
	// Controls rotation (radians/seconds)
	float mAngularSpeed;
	// Controls forward movement (units/second)
	float mForwardSpeed;
	// Newtonian physics
	// mass: a scalar that represent the quantity of matter contained in an object
	// mass is independent of gravity
	// the greater the mass of an object, the more difficult it is to change the movement of that object
	float mass; // how much matter
	// Force = mass x acceleration 
	// acceleration the rate at which the velocity of an object increases
	// acceleration is force divided by mass

	// An arbitrary object in the game has a mass, and you can apply forces to that object -> you can then compute the acceleration of the object
	float gravity; // GF: attractive forces between ALL objects with mass
	// Depends on the mass of the two objects: More mass, more GF 
	// and the distance: More distance, less GF
	// Example: Earth - it is massive ~6x10^24 kg, so it has a strong GF versus a lamp that is 1kg, so when we jump we are brough back down to earth not the lamp
	// -- You would have to get far away from Earth to not be affected by its gravitational force
	// -- The moon is 240,000 miles (400,000 km) away from Earth but it still feels affects from Earths gravity, that's why it orbits Earth
	// -- The moon is pretty big and we do experience the affects of its GF, this is why we have tides (pulls on Earth's water)
	// Why aren't we stuck to the ground then? Gravity is a weak force. We only notice its affects from massive objects like planets and stars. Not a lamp
	// Gravity exerted on us is weaker than forces we exert every day
	//float inertia;
	//float engineNormal;
	//float engineImpulse;
	Vector2 sumOfForces;

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

