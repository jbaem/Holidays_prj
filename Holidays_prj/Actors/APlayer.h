#pragma once

#include "../Common.h"
#include "APawn.h"


class APlayer : public APawn
{
public:
	APlayer() = delete;
	APlayer(EResourceID InID)
		:APawn(InID) {};
	virtual ~APlayer() = default;

	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;

	// Getter
	inline EPlayerState GetState() const { return State; }

	// Setter
	void SetState(EPlayerState InState);

private:
	void UpdateAnimation(float DeltaTime);

	EPlayerState State = EPlayerState::Move;
	EPlayerDirection FacingDirection = EPlayerDirection::Right;

	Gdiplus::Bitmap* IdleSprite = nullptr;
	Gdiplus::Bitmap* MoveSprite = nullptr;

	int CurrentFrameIndex = 0;
	float AnimationTimer = 0.0f;
	int TotalFrames = 10;
	float TimePerFrame = 1.0f / 15.0f;
};

