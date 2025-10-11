#pragma once

#include "Animator.h"

#include <unordered_map>
#include "../Enums.h"
#include "../Actors/APlayer.h"

class PlayerAnimator : public Animator
{
public:
	PlayerAnimator(AActor* InOwner);
	virtual ~PlayerAnimator();

	virtual void OnTick(float DeltaTime) override;

	void UpdateAnimation();

	bool IsAttackState() const { return State == EPlayerState::Attack1 || State == EPlayerState::Attack2; }
	bool IsOnGround() const { return State == EPlayerState::Idle || State == EPlayerState::Move || State == EPlayerState::Crouch; }
	bool IsDashState() const { return State == EPlayerState::Dash; }
	bool IsShootState() const { return State == EPlayerState::Shoot; }

	// Getter & Setter
	void SetState(EPlayerState InState);
	EPlayerState GetState() const { return State; }

private:
	EPlayerState State = EPlayerState::Idle;
};

