#pragma once

#include "Component.h"

#include <string>
#include <map>
#include "../Enums.h"

#include "FAnimation.h"

class Animator : public Component
{
public:
	Animator(AActor* InOwner)
		: Component(InOwner, EComponentType::Animator)
	{};
	virtual ~Animator() = default;
	
	virtual void OnTick(float DeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

	void AddAnimation(int AnimationNumber, FAnimation* InAnimation);
	void PlayAnimation(int AnimationNumber);

	Gdiplus::RectF GetCurrentFrameSourceRect() const;
	Gdiplus::Bitmap* GetCurrentSpriteSheet() const;

protected:
	std::wstring PlayerStateToString(EPlayerState state);

	void TestDisplay(Gdiplus::Graphics* InGraphics);

	std::map<int, FAnimation*> Animations;
	FAnimation* CurrentAnimation = nullptr;
	
	int CurrentFrameIndex = 0;
	float AnimationTimer = 0.0f;
	int bIsFinished = false;
};

