#pragma once

#include "Component.h"
#include "../Enums.h"
#include "../Actors/AActor.h"

class CircleCollider;
class RectangleCollider;

class Collider : public Component
{
public:
	Collider(AActor* InOwner, EPhysicsLayer InLayer)
		: Component(InOwner, EComponentType::Collider), Layer(InLayer) 
	{
		Center = InOwner->GetPivot();
	}
	virtual ~Collider() = default;

	virtual bool IsCollision(Collider* Other) = 0;
	
	virtual bool CheckCollisionWith(CircleCollider* Other) = 0;
	virtual bool CheckCollisionWith(RectangleCollider* Other) = 0;
	// Getter
	inline Gdiplus::PointF GetCenter() const { return Center; }
	inline EPhysicsLayer GetLayer() { return Layer; }
	// Setter
	inline void SetCenter(float x, float y) { Center = { x,y }; }

protected:
	Gdiplus::PointF Center = { 0.0f, 0.0f };
	EPhysicsLayer Layer = EPhysicsLayer::None;
};

