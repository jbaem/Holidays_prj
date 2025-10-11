#pragma once

#include "../Common.h"
#include "APawn.h"


class APlayer : public APawn
{
public:
	APlayer() = delete;
	APlayer(EResourceID InID) : APawn(EResourceID::None) {};
	virtual ~APlayer() = default;

	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;

	void SetLook(ELook InDirection) { Look = InDirection; }
	void SetState(EPlayerState InState) { if (State != InState) State = InState; }
	inline EPlayerState GetState() const { return State; }
	inline ELook GetLook() const { return Look; }

	bool WasJustHit() const { return State == EPlayerState::Hit; }
	bool IsOnGround() const { return bIsOnGround; }
	bool IsMoving() const { return bIsMoving; }

	bool bIsOnGround = false;
	bool bCanJump = true;

	bool bCanMove = true;
	bool bIsMoving = false;

	bool bCanCrouch = true;
	bool bIsCrouching = false;

	bool bCanDash = true;
	bool bIsDashing = false;

private:
	EPlayerState State = EPlayerState::Idle;

	const float ImageScale = 2.0f;
	const Gdiplus::PointF FrameSize = { 120.0f, 80.0f };

	float MoveSpeed = 250.0f;
	float DashSpeed = 1000.0f;
	float JumpSpeed = 500.0f;
};

