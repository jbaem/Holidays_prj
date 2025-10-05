#pragma once

#include "../Common.h"

class AActor
{
public:
	AActor() = delete;
	AActor(ResourceID InID);
	virtual ~AActor() = default;

	virtual void OnInitialize() {}
	virtual void OnDestroy() {}
	virtual void OnTick() {}
	virtual void OnRender() {}

protected:
	Gdiplus::PointF Position = { 0.0f, 0.0f };
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };

	float Angle = 0.0f;
	int Width = 64;
	int Height = 64;

	Gdiplus::Bitmap* Image = nullptr;
};

