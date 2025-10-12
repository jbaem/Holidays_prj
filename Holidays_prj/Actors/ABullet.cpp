#include "ABullet.h"
#include "ATerrain.h"
#include "../Managers/GameManager.h"

void ABullet::OnInitialize()
{
	AActor::OnInitialize();

    AddComponent(new Physics(this));
    AddComponent(new CircleCollider(this, EPhysicsLayer::Bullet, Size.X * 0.5f));

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

	LifeTime -= DeltaTime;
    if (LifeTime <= 0.0f)
        Destroy();

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

    if(!Image || !InGraphics)
        return;
    
    Gdiplus::RectF DestRect = {
        GetRenderPosition().X,
        GetRenderPosition().Y,
        Size.X,
        Size.Y
    };

    Gdiplus::GraphicsState originalState = InGraphics->Save();
    // 방향이 왼쪽(음수)이면 X축 반전
    if (Direction.X < 0)
    {
        InGraphics->TranslateTransform(DestRect.X + DestRect.Width / 2.0f, DestRect.Y + DestRect.Height / 2.0f);
        InGraphics->ScaleTransform(-1.0f, 1.0f);
        InGraphics->TranslateTransform(-(DestRect.X + DestRect.Width / 2.0f), -(DestRect.Y + DestRect.Height / 2.0f));
    }
    InGraphics->DrawImage(
        Image,
        DestRect,
        0, 0, SpriteSize.X, SpriteSize.Y,
        Gdiplus::UnitPixel
    );
    InGraphics->Restore(originalState);
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