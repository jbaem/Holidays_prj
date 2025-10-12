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

protected:
	Gdiplus::PointF Direction = { 1.0f, 0.0f };
    float Speed = 0.0f;
    float Damage = 0;
};