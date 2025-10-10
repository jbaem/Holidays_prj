#pragma once

#include "Animator.h"

#include <unordered_map>
#include "../Enums.h"
#include "../Actors/APlayer.h"

class APlayer;

class PlayerAnimator : public Animator
{
public:
	virtual ~PlayerAnimator() = default;
	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

	// Setter
	void SetState(EPlayerState InState);

private:
	void UpdateAnimation();

	bool bIsFinished = false;

	EPlayerState State = EPlayerState::None;
	EPlayerDirection FacingDirection = EPlayerDirection::Right;
	std::unordered_map<EPlayerState, Gdiplus::Bitmap*> SpritesMap;
};

