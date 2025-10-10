#pragma once


#include "Component.h"

#include <unordered_map>
#include "../Enums.h"

#include "FAnimation.h"


class Animator : public Component
{
public:
	Animator()
		: Component(EComponentType::Animator)
	{};
	virtual ~Animator() = default;
	
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override {};
	
protected:
	const float ImageScale = 2.0f;
	const Gdiplus::PointF FrameSize = { 120.0f, 80.0f };

	FAnimation CurrentAnimation;
};

