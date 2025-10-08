#pragma once

#include "AActor.h"

#include "../Common.h"
#include "../Enums.h"

class APawn : public AActor
{
	APawn(EResourceID InID)
		: AActor(InID) {}
	virtual ~APawn() = default;

	virtual void OnInitialize();
	virtual void OnDestroy() {}
	virtual void OnTick(float DeltaTime) {}
	virtual void OnRender(Gdiplus::Graphics* InGraphics) {}

	virtual void OnOverlap(AActor* Other) {}


	virtual void TakeDamage(float InDamage);
	virtual void Move(const Gdiplus::PointF& InDirection);

	// Getter
	inline float GetHealth() const { return Health; }

protected:
	float Health = 100.0f;
	float MoveSpeed = 20000.0f;
};

