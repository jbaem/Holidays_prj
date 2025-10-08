#pragma once

#include "../Common.h"
#include "AActor.h"


class APlayer : public AActor
{
public:
	APlayer() = delete;
	APlayer(EResourceID InID) : AActor(InID) {};

	virtual void OnInitialize() override {};
	virtual void OnDestroy() override {};
	virtual void OnTick(float DeltaTime) override {};
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override {};

	virtual void OnOverlap(AActor* Other) override {};

	// Getter
	inline float GetSpeed() const { return Speed; }
	inline EPlayerState GetState() const { return State; }

	// Setter
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }
	inline void SetState(EPlayerState InState) { State = InState; }

private:
	float Speed = 200.0f;

	EPlayerState State = EPlayerState::Idle;
};

