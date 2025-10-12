#pragma once

#include "Collider.h"

#include "../Common.h"

class RectangleCollider : public Collider
{
public:
	RectangleCollider(AActor* InOwner, EPhysicsLayer InLayer, float InWidth, float InHeight)
		:Collider(InOwner, InLayer), Width(InWidth), Height(InHeight) {
	}
	virtual ~RectangleCollider() = default;

	virtual void OnRender(Gdiplus::Graphics* InGraphics) override
	{
		// DEBUG: Debug Draw
		/*Gdiplus::Pen pen(Gdiplus::Color(255, 0, 255, 0));
		Gdiplus::PointF Center = GetCenter();
		InGraphics->DrawRectangle(
			&pen,
			Center.X - Width * 0.5f,
			Center.Y - Height * 0.5f,
			Width,
			Height
		);*/
	}

	virtual bool IsCollision(Collider* Other) override;

	virtual bool CheckCollisionWith(CircleCollider* Other) override;
	virtual bool CheckCollisionWith(RectangleCollider* Other) override;
	// Getter
	inline float GetWidth() const { return Width; }
	inline float GetHeight() const { return Height; }
	// Setter
	inline void SetSize(float InWidth, float InHeight) { Width = InWidth; Height = InHeight; }
private:
	float Width = 0.0f;
	float Height = 0.0f;
};

