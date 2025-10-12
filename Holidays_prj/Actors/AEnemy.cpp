#include "AEnemy.h"
#include "ATerrain.h"
#include "../Managers/GameManager.h"
#include "../Managers/Factory.h"
#include "../Components/PlayerAnimator.h"
#include "../Managers/UIManager.h"
#include "APlayerBullet.h"

void AEnemy::OnInitialize()
{
	APawn::OnInitialize();
	SetSize(FrameSize.X * ImageScale, FrameSize.Y * ImageScale);
	Collider* MyCollider = GetComponent<CircleCollider>();
	if (MyCollider)
	{
		static_cast<CircleCollider*>(MyCollider)->SetRadius(GetSize().Y * 0.30f);
		MyCollider->SetLayer(EPhysicsLayer::Enemy);
	}
	
	Physics* MyPhysics = GetComponent<Physics>();
	if (MyPhysics)
	{
		MyPhysics->SetEnableGravity(false);
		MyPhysics->SetMaxVelocity(100.0f, 100.0f);
	}
	
	Health = 30.0f;
}

void AEnemy::OnTick(float DeltaTime)
{
	APlayer* Player = GameManager::GetInstance().GetMainPlayer();
	Physics* MyPhysics = GetComponent<Physics>();
	if (Player && MyPhysics)
	{
		Gdiplus::PointF MyPos = GetPosition();
		Gdiplus::PointF PlayerPos = Player->GetPosition();
		Gdiplus::PointF ForceDirection = { PlayerPos.X - MyPos.X, PlayerPos.Y - MyPos.Y };
		float VectorLength = sqrt(ForceDirection.X * ForceDirection.X + ForceDirection.Y * ForceDirection.Y);
		if (VectorLength > 0.01f) {
			ForceDirection.X /= VectorLength;
			ForceDirection.Y /= VectorLength;
		}
		Move(ForceDirection);
	}
	
	if(MyPhysics->GetVelocity().X > 0)
	{
		Look = ELook::Right;
	}
	else if(MyPhysics->GetVelocity().X < 0)
	{
		Look = ELook::Left;
	}

	if(GetHealth() <= 0.0f)
	{
		Destroy();
	}
	
	APawn::OnTick(DeltaTime);
}

void AEnemy::OnRender(Gdiplus::Graphics* InGraphics)
{
	APawn::OnRender(InGraphics);


	if (!InGraphics || !Image)
		return;
	
	Gdiplus::RectF DestRect(
		GetRenderPosition().X, 
		GetRenderPosition().Y,
		GetSize().X, GetSize().Y
	);

	Gdiplus::GraphicsState originalState = InGraphics->Save();
	Physics* MyPhysics = GetComponent<Physics>();
	
	if (Look == ELook::Left)
	{
		InGraphics->TranslateTransform(DestRect.X + DestRect.Width / 2.0f, DestRect.Y + DestRect.Height / 2.0f);
		InGraphics->ScaleTransform(-1.0f, 1.0f);
		InGraphics->TranslateTransform(-(DestRect.X + DestRect.Width / 2.0f), -(DestRect.Y + DestRect.Height / 2.0f));
	}

	InGraphics->DrawImage(
		Image, 
		DestRect, 
		0.0f, 0.0f, FrameSize.X, FrameSize.Y, 
		Gdiplus::UnitPixel
	);

	InGraphics->Restore(originalState);
}

void AEnemy::OnOverlap(AActor* Other)
{
	APlayer* Player = dynamic_cast<APlayer*>(Other);
	if (Player)
	{
		Player->TakeDamage(10.0f);
		Destroy();
		return;
	}
}

void AEnemy::Destroy()
{
	UIManager::GetInstance().AddEnemyKillCount();
	AActor::Destroy();
}

void AEnemy::TakeDamage(float InDamage)
{
	Physics* MyPhysics = GetComponent<Physics>();
	MyPhysics->SetVelocityX(
		Look == ELook::Left ? 500.0f : -500.0f
	);	

	APawn::TakeDamage(InDamage);
}
