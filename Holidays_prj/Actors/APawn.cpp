#include "APawn.h"

#include "../Components/CircleCollider.h"
#include "../Components/Physics.h"

void APawn::OnInitialize()
{
	AActor::OnInitialize();

	AddComponent(new Physics(this));
	AddComponent(new CircleCollider(this, EPhysicsLayer::Pawn, GetSize().Y * 0.5f));
}

void APawn::OnTick(float DeltaTime)
{
	AActor::OnTick(DeltaTime);
}

void APawn::OnRender(Gdiplus::Graphics* InGraphics)
{
	AActor::OnRender(InGraphics);
}

void APawn::TakeDamage(float InDamage)
{
	Health -= InDamage;
	if (Health < 0.0f)
	{
		Health = 0.0f;
		Destroy();
	}
}

void APawn::Move(const Gdiplus::PointF& InDirection)
{
	Physics* MyPhysics = GetComponent<Physics>();
	if (MyPhysics)
	{
		Gdiplus::PointF Force = {
			InDirection.X * MoveForce,
			InDirection.Y * MoveForce
		};
		MyPhysics->AddForce(Force);
	}
}
