#pragma once

#include "../Common.h"

#include "Component.h"


constexpr float GRAVITY = 980.0f;

class Physics : public Component
{
public:
	Physics(AActor* InOwner) 
		: Component(InOwner, EComponentType::Physics) {}

	virtual void OnTick(float DeltaTime) override;
	void AddForce(const Gdiplus::PointF& InForce);

private:
	Gdiplus::PointF Velocity = { 0.f, 0.f };
	Gdiplus::PointF Acceleration = { 0.0f, 0.0f };

	float Mass = 1.0f;
	float LinearDamping = 0.99f;

	bool bEnableGravity = true;
};

