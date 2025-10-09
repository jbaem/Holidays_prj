#pragma once

#include "AActor.h"

class ABackground : public AActor
{
public:
	ABackground(EResourceID InID)
		:AActor(InID)
	{
		Size = { 1280.f, 720.f };
	}
	virtual ~ABackground() = default;

	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
};

