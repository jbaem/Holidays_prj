#include "AEnemyBullet.h"



#include "../Managers/GameManager.h"
#include "../Actors/APlayer.h"


void AEnemyBullet::OnInitialize()
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

	Speed = 600.0f;
	Damage = 10.0f;

	SetSize(16.0f, 16.0f);
	GetComponent<CircleCollider>()->SetRadius(4.0f);
	GetComponent<CircleCollider>()->SetOffset(0.0f, 0.0f);
	GetComponent<CircleCollider>()->SetLayer(EPhysicsLayer::PlayerBullet);
}

void AEnemyBullet::OnTick(float DeltaTime)
{
	ABullet::OnTick(DeltaTime);
}

void AEnemyBullet::OnRender(Gdiplus::Graphics* InGraphics)
{
	ABullet::OnRender(InGraphics);
}

void AEnemyBullet::OnOverlap(AActor* Other)
{
	APlayer* Player = dynamic_cast<APlayer*>(Other);
	if (Player)
	{
		Player->TakeDamage(Damage);
		Destroy();
		return;
	}

	ABullet::OnOverlap(Other);
}
