#include "InputComponent.h"
#include "Actor.h"
#include <iostream>
InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
	, mForce(0,0)
	, isFMoving(false)
	, isBMoving(false)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{	
		isFMoving = true;
		mForce.x += GetMass() * GetMaxForward() / 40;
		AddForces(mForce);
		if (mForce.x >= GetMaxForward() * GetMass())
			mForce.x = GetMaxForward() * GetMass();
	}
	if ((!keyState[mForwardKey]) && isFMoving)
	{
		mForce.x -= GetMass() * GetMaxForward() / 60;
		if (mForce.x <= 0)
		{
			mForce.x = 0;
			isFMoving = false;
		}
		AddForces(mForce);
	}
	if ((!keyState[mBackKey]) && isBMoving)
	{
		mForce.x += GetMass() * GetMaxForward() / 60;
		if (mForce.x >= 0)
		{
			mForce.x = 0;
			isBMoving = false;
		}
		AddForces(mForce);
	}
	if (keyState[mBackKey])
	{
		isBMoving = true;
		mForce.x -= GetMass() * GetMaxForward() / 40;
		AddForces(mForce);
		if (mForce.x <= -(GetMaxForward() * GetMass()))
			mForce.x = -(GetMaxForward() * GetMass());
	}
	SetForwardSpeed(mForce.x);

	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}