#pragma once

#include "../Common.h"

#include "Component.h"


constexpr float GRAVITY = 98.0f * 5;

class Physics : public Component
{
public:
	Physics(AActor* InOwner) 
		: Component(InOwner, EComponentType::Physics) {}

	virtual void OnTick(float DeltaTime) override;
	void AddForce(const Gdiplus::PointF& InForce);

	// Getter
	inline Gdiplus::PointF& GetVelocity() { return Velocity; }
	inline Gdiplus::PointF& GetAcceleration() { return Acceleration; }

	// Setter
	inline void SetVelocityX(float InVelocityX) { Velocity.X = InVelocityX; }
	inline void SetVelocityY(float InVelocityY) { Velocity.Y = InVelocityY; }
	inline void SetEnableGravity(bool bEnable) { this->bEnableGravity = bEnable; }


private:
	Gdiplus::PointF Velocity = { 0.f, 0.f };
	Gdiplus::PointF Acceleration = { 0.0f, 0.0f };

	float Mass = 1.0f;
	float LinearDamping = 0.99f;
	Gdiplus::PointF MaxVelocity = { 1000.0f, 400.0f };
	
	bool bEnableGravity = true;
};

