#pragma once

#include "../Common.h"
#include "APawn.h"


class APlayer : public APawn
{
public:
	APlayer() = delete;
	APlayer(EResourceID InID) : APawn(InID) {};
	virtual ~APlayer() = default;

	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;

	void InitStats();

	bool bCanMove = true;
	bool bIsMoving = false;

	bool bIsCrouching = false;
	bool bCanCrouch = true;

	bool bCanDash = true;
	bool bIsDashing = false;

	bool bCanJump = true;
	bool bIsJumping = false;

private:
	const float ImageScale = 2.0f;
	const Gdiplus::PointF FrameSize = { 120.0f, 80.0f };

	float JumpSpeed = 600.0f;
};

