#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(AActor* InOwner, EPhysicsLayer InLayer, float InRadius)
		: Collider(InOwner, InLayer), Radius(InRadius) {
	}
	virtual ~CircleCollider() = default;

	virtual void OnRender(Gdiplus::Graphics* InGraphics) override
	{
		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 255, 0));
		Gdiplus::PointF Center = GetCenter();
		InGraphics->DrawEllipse(
			&pen,
			Center.X - Radius,
			Center.Y - Radius,
			Radius * 2,
			Radius * 2
		);
	}

	virtual bool IsCollision(Collider* Other) override;

	virtual bool CheckCollisionWith(CircleCollider* Other) override;
	virtual bool CheckCollisionWith(RectangleCollider* Other) override;
	// Getter
	inline float GetRadius() const { return Radius; }
	// Setter
	inline void SetRadius(float InRadius) { Radius = InRadius; }
private:
	float Radius = 0.0f;
};

