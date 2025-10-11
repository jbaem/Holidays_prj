#include "Physics.h"

#include "../Actors/AActor.h"
#include "../Actors/APlayer.h"

void Physics::OnTick(float DeltaTime)
{
	if (bEnableGravity)
	{
		AddForce({ 0.0f, GRAVITY });
	}

	Velocity.X += Acceleration.X * DeltaTime;
	Velocity.Y += Acceleration.Y * DeltaTime;

	if (Velocity.X >  MaxVelocity.X) Velocity.X =  MaxVelocity.X;
	if (Velocity.X < -MaxVelocity.X) Velocity.X = -MaxVelocity.X;

	if (Velocity.Y >  MaxVelocity.Y) Velocity.Y =  MaxVelocity.Y;
	if (Velocity.Y < -MaxVelocity.Y) Velocity.Y = -MaxVelocity.Y;

	Velocity.X *= LinearDamping;
	Velocity.Y *= LinearDamping;

	if (Owner)
	{
		Gdiplus::PointF CurrentPosition = Owner->GetPosition();
		CurrentPosition.X += Velocity.X * DeltaTime;
		CurrentPosition.Y += Velocity.Y * DeltaTime;
		Owner->SetPosition(CurrentPosition.X, CurrentPosition.Y);
	}
	Acceleration = { 0.0f, 0.0f };
}

void Physics::AddForce(const Gdiplus::PointF& InForce)
{
	if (Mass > 0.0001f)
	{
		Acceleration.X += InForce.X / Mass;
		Acceleration.Y += InForce.Y / Mass;
	}
}
