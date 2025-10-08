#include "Physics.h"

#include "../Actors/AActor.h"

void Physics::OnTick(float DeltaTime)
{
	if (bEnableGravity)
	{
		AddForce({ 0.0f, GRAVITY });
	}

	// 가속 (가속도)
	Velocity.X += Acceleration.X * DeltaTime;
	if (Velocity.X >  MaxVelocity.X) Velocity.X =  MaxVelocity.X;
	if (Velocity.X < -MaxVelocity.X) Velocity.X = -MaxVelocity.X;

	Velocity.Y += Acceleration.Y * DeltaTime;
	if (Velocity.Y >  MaxVelocity.Y) Velocity.Y =  MaxVelocity.Y;
	if (Velocity.Y < -MaxVelocity.Y) Velocity.Y = -MaxVelocity.Y;

	// 감속 (저항)
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
