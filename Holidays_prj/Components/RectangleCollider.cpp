#include "RectangleCollider.h"
#include "CircleCollider.h"

#include <algorithm>

#include "../Actors/AActor.h";

bool RectangleCollider::IsCollision(Collider* Other)
{
	return Other->CheckCollisionWith(this);
}

bool RectangleCollider::CheckCollisionWith(CircleCollider* Other)
{
    // Circle
    Gdiplus::PointF CircleCenter = Other->GetCenter();
    float CircleRadius = Other->GetRadius();

    // Rectangle
    Gdiplus::PointF RectCenter = this->GetCenter();
    float RectWidth = this->GetWidth();
    float RectHeight = this->GetHeight();

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

bool RectangleCollider::CheckCollisionWith(RectangleCollider* Other)
{
    Gdiplus::PointF MyCenter = this->GetCenter();
    float MyWidth = this->GetWidth();
    float MyHeight = this->GetHeight();
    Gdiplus::RectF a(
        MyCenter.X - MyWidth * 0.5f,
        MyCenter.Y - MyHeight * 0.5f,
        MyWidth,
        MyHeight);

    Gdiplus::PointF OtherCenter = Other->GetCenter();
    float OtherWidth = Other->GetWidth();
    float OtherHeight = Other->GetHeight();
    Gdiplus::RectF b(
        OtherCenter.X - OtherWidth * 0.5f,
        OtherCenter.Y - OtherHeight * 0.5f,
        OtherWidth,
        OtherHeight);

    //AABB Collision
    return !(a.GetRight() < b.GetLeft() || a.GetLeft() > b.GetRight() || a.GetBottom() < b.GetTop() || a.GetTop() > b.GetBottom());
}
