#pragma once

#include "ABullet.h"

class AEnemyBullet : public ABullet
{
public:
	AEnemyBullet(EResourceID InID)
		: ABullet(InID) {}
	virtual ~AEnemyBullet() = default;

	virtual void OnInitialize() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(AActor* Other) override;



};

