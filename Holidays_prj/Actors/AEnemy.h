#pragma once

#include "APawn.h"
#include "../Components/Physics.h"
#include "../Components/CircleCollider.h"
#include "../Components/RectangleCollider.h"
#include "../Managers/ResourceManager.h"
#include "../Components/PlayerAnimator.h"

class AEnemy : public APawn
{
public:
	AEnemy() = delete;
	AEnemy(EResourceID InID)
		: APawn(InID)
	{
	}

	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;
	virtual void Destroy() override;

	virtual void TakeDamage(float InDamage) override;

private:
	Gdiplus::PointF FrameSize = { 72.0f, 72.0f }; 
	float ImageScale = 2.0f; 

	ELook Look = ELook::Left;
};