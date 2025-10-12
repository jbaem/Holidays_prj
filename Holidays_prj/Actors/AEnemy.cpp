#include "AEnemy.h"

#include "../Components/CircleCollider.h"

void AEnemy::OnInitialize()
{
	APawn::OnInitialize();

	Collider* MyCollider = GetComponent<CircleCollider>();
	MyCollider->SetOffset(-GetSize().X * 0.05f, GetSize().Y * 0.30f);
	static_cast<CircleCollider*>(MyCollider)->SetRadius(GetSize().Y * 0.20f);


	MyCollider->SetLayer(EPhysicsLayer::Enemy);
}

void AEnemy::OnTick(float DeltaTime)
{
	APawn::OnTick(DeltaTime);
}

void AEnemy::OnRender(Gdiplus::Graphics* InGraphics)
{
	APawn::OnRender(InGraphics);
}

void AEnemy::OnOverlap(AActor* Other)
{
	APawn::OnOverlap(Other);
}
