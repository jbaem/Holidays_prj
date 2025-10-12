#pragma once

#include "ABullet.h"

class APlayerBullet : public ABullet
{
public:
	APlayerBullet(EResourceID InID)
		: ABullet(InID) {}
	virtual ~APlayerBullet() = default;
	
	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;
};

