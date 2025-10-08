#pragma once

#include "AActor.h"

#include "../Common.h"
#include "../Enums.h"

class APawn : public AActor
{
public:
	APawn(EResourceID InID)
		: AActor(InID) {}
	virtual ~APawn() = default;

	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void TakeDamage(float InDamage);
	virtual void Move(const Gdiplus::PointF& InDirection);

	// Getter
	inline float GetHealth() const { return Health; }

protected:
	float Health = 100.0f;
	float MoveForce = 50000.0f;
};

