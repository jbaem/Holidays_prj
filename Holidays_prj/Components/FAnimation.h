#pragma once

struct FAnimation
{
	Gdiplus::Bitmap* SpriteSheet = nullptr;
	int TotalFrames = 1;
	float FPS = 15.0f;
	bool bIsLoop = true;

	FAnimation() = default;
	FAnimation(Gdiplus::Bitmap* InSprite, int InTotalFrames, float InFPS, bool InbIsLoop)
		:SpriteSheet(InSprite), 
		TotalFrames(InTotalFrames), 
		FPS(InFPS), 
		bIsLoop(InbIsLoop) { }
};
