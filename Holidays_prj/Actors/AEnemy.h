#pragma once

#include "APawn.h"
#include "APlayer.h"

class AEnemy : public APawn
{
public:
	AEnemy() = delete;
	AEnemy(EResourceID InID) : APawn(InID) {};
	virtual ~AEnemy() = default;

	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;
	
	//void SetState() {}

protected:
	const float ImageScale = 2.0f;
	const Gdiplus::PointF FrameSize = { 120.0f, 80.0f };

	float PatrolRadius = 200.0f;

	APlayer* MainPlayer = nullptr;

	Gdiplus::PointF NextPosition = { 0.0f, 0.0f };
	
	Gdiplus::PointF StartPosition = { 0.0f, 0.0f };
};