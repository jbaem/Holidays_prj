#pragma once

#include "AActor.h"
#include "../Components/Physics.h"
#include "../Components/CircleCollider.h"

class ABullet : public AActor
{
public:
    ABullet(EResourceID InID)
		:AActor(InID) {}
    virtual ~ABullet() = default;

    virtual void OnInitialize() override;
    virtual void OnTick(float DeltaTime) override;
    virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;

    Physics* GetPhysics() { return GetComponent<Physics>(); }
    CircleCollider* GetCollider() { return GetComponent<CircleCollider>(); }

	void SetDirection(const Gdiplus::PointF& InDirection) { Direction = InDirection; }
	void SetLifeTime(float InLifeTime) { LifeTime = InLifeTime; }

protected:
	Gdiplus::PointF SpriteSize = { 16.0f, 16.0f };
	Gdiplus::PointF Direction = { 1.0f, 0.0f };
    float Speed = 0.0f;
    float Damage = 0;

    float LifeTime = 10.0f;
};