#include "CircleCollider.h"
#include "RectangleCollider.h"

#include "../Actors/AActor.h"
#include "../Common.h"

CircleCollider::CircleCollider(AActor* InOwner, EPhysicsLayer InLayer, float InRadius)
    : Collider(InOwner, InLayer), Radius(InRadius) {}

bool CircleCollider::IsCollision(Collider* Other)
{
	return Other->CheckCollisionWith(this);
}

bool CircleCollider::CheckCollisionWith(CircleCollider* Other)
{
    // Center
    Gdiplus::PointF MyCenter = this->GetCenter();
    Gdiplus::PointF OtherCenter = Other->GetOwner()->GetPosition();

    // Distance
    float dx = MyCenter.X - OtherCenter.X;
    float dy = MyCenter.Y - OtherCenter.Y;
    // Sum of Radius
    float SumRadius = this->GetRadius() + Other->GetRadius();
    return IsAcuteTriangle(dx, dy, SumRadius);
}

bool CircleCollider::CheckCollisionWith(RectangleCollider* Other)
{
    // Circle
    Gdiplus::PointF CircleCenter = this->GetCenter();
    float CircleRadius = this->GetRadius();

    // Rectangle
    Gdiplus::PointF RectCenter = Other->GetCenter();
    float RectWidth = Other->GetWidth();
    float RectHeight = Other->GetHeight();
    
    // Closest
    float closestX = Clamp(
        CircleCenter.X, 
        RectCenter.X - RectWidth * 0.5f,
        RectCenter.X + RectWidth * 0.5f
    );
    float closestY = Clamp(
        CircleCenter.Y, 
        RectCenter.Y - RectHeight * 0.5f,
        RectCenter.Y + RectHeight * 0.5f
    );

    // Distance
    float dx = CircleCenter.X - closestX;
    float dy = CircleCenter.Y - closestY;
    
    return IsAcuteTriangle(dx, dy, CircleRadius);
}
