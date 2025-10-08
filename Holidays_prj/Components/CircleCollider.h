#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(AActor* InOwner, EPhysicsLayer InLayer, float InRadius);
	virtual ~CircleCollider() = default;

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

