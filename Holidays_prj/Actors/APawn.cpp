#include "APawn.h"

#include "../Components/CircleCollider.h"
#include "../Components/Physics.h"

void APawn::OnInitialize()
{
	AddComponent(new Physics(this));
	AddComponent(new CircleCollider(this, EPhysicsLayer::Pawn, Size.X / 2.0f));
}

void APawn::TakeDamage(float InDamage)
{
	Health -= InDamage;
	if (Health < 0.0f)
	{
		Health = 0.0f;
		// TODO : »ç¸Á ·ÎÁ÷
	}

}

void APawn::Move(const Gdiplus::PointF& InDirection)
{
	Physics* MyPhysics = GetComponent<Physics>();
	if (MyPhysics)
	{
		Gdiplus::PointF Force = {
			InDirection.X * MoveSpeed,
			InDirection.Y * MoveSpeed
		};
		MyPhysics->AddForce(Force);
	}
}
