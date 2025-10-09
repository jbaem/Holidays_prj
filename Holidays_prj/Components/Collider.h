#pragma once

#include "Component.h"
#include "../Enums.h"
#include "../Actors/AActor.h"

class CircleCollider;
class RectangleCollider;

class Collider : public Component
{
public:
	Collider(EPhysicsLayer InLayer)
		: Component(EComponentType::Collider), Layer(InLayer) 
	{
	}
	virtual ~Collider() = default;

	virtual bool IsCollision(Collider* Other) = 0;
	
	virtual bool CheckCollisionWith(CircleCollider* Other) = 0;
	virtual bool CheckCollisionWith(RectangleCollider* Other) = 0;
	
	virtual Gdiplus::PointF GetCenter() { 
		Gdiplus::PointF OwnerPos = Owner->GetPosition();
		return { OwnerPos.X + Offset.X, OwnerPos.Y + Offset.Y };
	}
	// Getter
	inline EPhysicsLayer GetLayer() { return Layer; }

	// Setter
	inline void SetOffset(float x, float y) { Offset = { x, y }; }
	inline void SetLayer(EPhysicsLayer InLayer) { Layer = InLayer; }

protected:
	Gdiplus::PointF Offset = { 0.0f, 0.0f };
	EPhysicsLayer Layer = EPhysicsLayer::None;
};

