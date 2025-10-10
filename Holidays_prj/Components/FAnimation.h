#pragma once

struct FAnimation
{
	int CurrentFrameIndex = 0;
	float Timer = 0.0f;
	int TotalFrames = 1;
	float TimePerFrame = 1.0f / 15.0f; 
	bool bIsLooping = true;
	bool bIsFinished = false;

	FAnimation() = default;

	bool Update(float DeltaTime)
	{
		if(bIsFinished)
			return false;

		Timer += DeltaTime;
		if(Timer >= TimePerFrame)
		{
			Timer -= TimePerFrame;
			CurrentFrameIndex = (CurrentFrameIndex + 1) % TotalFrames;
		}

		if (!bIsLooping && CurrentFrameIndex == TotalFrames - 1)
		{
			bIsFinished = true;
		}
		else
		{
			bIsFinished = false;
		}
		return true;
	}

	void Reset()
	{
		CurrentFrameIndex = 0;
		Timer = 0.0f;
		bIsFinished = false;
	}

	void SetAnimation(int InTotalFrames, float InTimePerFrame, bool InIsLooping)
	{
		TotalFrames = InTotalFrames;
		TimePerFrame = InTimePerFrame;
		bIsLooping = InIsLooping;
		Reset();
	}
};
