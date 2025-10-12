#include "APlayerBullet.h"

#include "../Managers/GameManager.h"
#include "../Actors/AEnemy.h"


void APlayerBullet::OnInitialize()
{
	ABullet::OnInitialize();

	APlayer* player = GameManager::GetInstance().GetMainPlayer();
	if (!player) return;

	// 방향 설정 (플레이어의 ELook 기준)
	if (player->GetLook() == ELook::Right)
		Direction = { 1.0f, 0.0f };
	else
		Direction = { -1.0f, 0.0f };

	Gdiplus::PointF playerPos = player->GetPosition();
	Gdiplus::PointF bulletPos = {
		playerPos.X + Direction.X * 32.0f,
		playerPos.Y + Direction.Y * 32.0f
	};
	SetPosition(bulletPos);

	Speed = 400.0f;
	Damage = 10.0f;

	SetSize(32.0f, 32.0f);
	GetComponent<CircleCollider>()->SetRadius(Size.X / 2.0f);
	GetComponent<CircleCollider>()->SetOffset(0.0f, 0.0f);
	GetComponent<CircleCollider>()->SetLayer(EPhysicsLayer::PlayerBullet);
}

void APlayerBullet::OnTick(float DeltaTime)
{
	ABullet::OnTick(DeltaTime);
}

void APlayerBullet::OnRender(Gdiplus::Graphics* InGraphics)
{
	ABullet::OnRender(InGraphics);
}

void APlayerBullet::OnOverlap(AActor* Other)
{
	AEnemy* Enemy = dynamic_cast<AEnemy*>(Other);
	if(Enemy)
	{
		Enemy->TakeDamage(Damage);
		Destroy();
		return;
	}

	ABullet::OnOverlap(Other);
}
