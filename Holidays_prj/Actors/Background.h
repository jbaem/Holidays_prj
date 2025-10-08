#pragma once

#include "AActor.h"

class Background : public AActor
{
public:
	Background(EResourceID InID)
		:AActor(InID)
	{
		Size = { 1280.f, 720.f };
	}
	virtual ~Background() = default;

	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
};

