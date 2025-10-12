#include "ABullet.h"
#include "ATerrain.h"
#include "../Managers/GameManager.h"

void ABullet::OnInitialize()
{
	AActor::OnInitialize();

    AddComponent(new Physics(this));
	AddComponent(new CircleCollider(this, EPhysicsLayer::Bullet, 4.0f));

    GetComponent<Physics>()->SetEnableGravity(false);
}

void ABullet::OnTick(float DeltaTime)
{
    Physics* physics = GetPhysics();
    if (physics)
    {
        GetComponent<Physics>()->SetVelocityX(Direction.X * Speed);
        GetComponent<Physics>()->SetVelocityY(Direction.Y * Speed);
    }
    AActor::OnTick(DeltaTime);

    // Out of Bounds Check
    Gdiplus::PointF pos = GetPosition();
    if (pos.X < 0 || pos.X > GameManager::ScreenWidth ||
        pos.Y < 0 || pos.Y > GameManager::ScreenHeight)
    {
        Destroy();
    }
}

void ABullet::OnRender(Gdiplus::Graphics* InGraphics)
{
    AActor::OnRender(InGraphics);
}

void ABullet::OnOverlap(AActor* Other)
{
    if (Other->GetComponent<Collider>()->GetLayer() == EPhysicsLayer::Terrain)
    {
		ATerrain* Terrain = dynamic_cast<ATerrain*>(Other);
        if (Terrain && Terrain->GetTerrainType() != EBlockType::OneWay)
        {
            Destroy();
            return;
        }
    }
}