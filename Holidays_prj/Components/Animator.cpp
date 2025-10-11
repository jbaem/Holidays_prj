#include "Animator.h"

#include <string>

#include "../Actors/AActor.h"
#include "../Actors/APlayer.h"
#include "PlayerAnimator.h"
#include "Physics.h"


// Change to Next frame by DeltaTime
void Animator::OnTick(float DeltaTime)
{
	if(!CurrentAnimation)
		return;

	AnimationTimer += DeltaTime;
	float TimePerFrame = 1.0f / CurrentAnimation->FPS;

	bIsFinished = false;
	if(AnimationTimer>=TimePerFrame)
	{
		AnimationTimer -= TimePerFrame;
		CurrentFrameIndex++;

		if(CurrentFrameIndex >= CurrentAnimation->TotalFrames)
		{
			if(CurrentAnimation->bIsLoop)
			{
				CurrentFrameIndex = 0;
			}
			else
			{
				CurrentFrameIndex = CurrentAnimation->TotalFrames - 1;
				bIsFinished = true;
			}
		}
	}
}

// Render Current Frame
void Animator::OnRender(Gdiplus::Graphics* InGraphics)
{
	Gdiplus::Bitmap* CurrentSprite = CurrentAnimation->SpriteSheet;
	if (!CurrentSprite)
		return;

	Gdiplus::GraphicsState originalState = InGraphics->Save();
	InGraphics->TranslateTransform(Owner->GetPosition().X, Owner->GetPosition().Y);
	if(Owner->GetLook() == ELook::Left)
	{
		InGraphics->ScaleTransform(-1.0f, 1.0f);
	}

	Gdiplus::PointF RenderPos = Owner->GetRenderPosition();
	const float FrameWidth = static_cast<float>(CurrentSprite->GetWidth()) / static_cast<float>(CurrentAnimation->TotalFrames);
	const float FrameHeight = (float)CurrentSprite->GetHeight();
	float SourceX = CurrentFrameIndex * FrameWidth;

	InGraphics->DrawImage(
		CurrentSprite,
		Gdiplus::RectF(
			RenderPos.X - Owner->GetPosition().X,
			RenderPos.Y - Owner->GetPosition().Y,
			Owner->GetSize().X, Owner->GetSize().Y),
		SourceX, 0, FrameWidth, FrameHeight,
		Gdiplus::UnitPixel
	);

	InGraphics->Restore(originalState);


	// Display Player State as text
	EPlayerState playerState = EPlayerState::Idle;
	if (Owner) {
		// Owner가 APlayer 타입일 때만 상태를 가져옴
		APlayer* player = dynamic_cast<APlayer*>(Owner);
		if (player) {
			playerState = player->GetComponent<PlayerAnimator>()->GetState(); // GetState() 함수가 있다고 가정
		}
	}
	std::wstring stateText = PlayerStateToString(playerState);

	Gdiplus::Font font(L"Arial", 16);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	InGraphics->DrawString(
		stateText.c_str(),
		-1,
		&font,
		Gdiplus::PointF(10, 10), // 화면 왼쪽 위
		&brush
	);

	APlayer* Player = static_cast<APlayer*>(Owner);
	if (Player)
	{
		Physics* MyPhysics = Player->GetComponent<Physics>();
		if (MyPhysics)
		{
			float velocityX = MyPhysics->GetVelocity().X;
			float velocityY = MyPhysics->GetVelocity().Y;
			std::wstring velocityTextX = L"Velocity.X: " + std::to_wstring(velocityX);
			std::wstring velocityTextY = L"Velocity.Y: " + std::to_wstring(velocityY);

			Gdiplus::Font font(L"Arial", 16);
			Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
			InGraphics->DrawString(
				velocityTextX.c_str(),
				-1,
				&font,
				Gdiplus::PointF(10, 100), // 화면 왼쪽 위
				&brush
			);

			InGraphics->DrawString(
				velocityTextY.c_str(),
				-1,
				&font,
				Gdiplus::PointF(10, 200), // 화면 왼쪽 위
				&brush
			);
		}
	}

}

// Add Animation to map
void Animator::AddAnimation(int AnimationNumber, FAnimation* InAnimation)
{
	Animations[AnimationNumber] = InAnimation;
}

// Play Animation by AnimationNumber
void Animator::PlayAnimation(int AnimationNumber)
{
	if(CurrentAnimation == Animations[AnimationNumber])
		return;

	auto findIt = Animations.find(AnimationNumber);
	if(findIt != Animations.end())
	{
		CurrentAnimation = findIt->second;
		CurrentFrameIndex = 0;
		AnimationTimer = 0.0f;
	}
}

// Get Source Rect of Current Frame
Gdiplus::RectF Animator::GetCurrentFrameSourceRect() const
{
	if(!CurrentAnimation || !CurrentAnimation->SpriteSheet)
		return Gdiplus::RectF();

	float FrameWidth = static_cast<float>(CurrentAnimation->SpriteSheet->GetWidth()) / CurrentAnimation->TotalFrames;
	float FrameHeight = static_cast<float>(CurrentAnimation->SpriteSheet->GetHeight());

	return Gdiplus::RectF(
		FrameWidth * CurrentFrameIndex,
		0.0f,
		FrameWidth,
		FrameHeight
	);
}

// Get Current Sprite Sheet
Gdiplus::Bitmap* Animator::GetCurrentSpriteSheet() const
{
	if(!CurrentAnimation)
		return nullptr;
	return CurrentAnimation->SpriteSheet;
}

std::wstring Animator::PlayerStateToString(EPlayerState state) {
	switch (state) {
	case EPlayerState::Idle: return L"Idle";
	case EPlayerState::Move: return L"Move";
	case EPlayerState::Attack1: return L"Attack1";
	case EPlayerState::Attack2: return L"Attack2";
	case EPlayerState::Shoot: return L"Shoot";
	case EPlayerState::Hit: return L"Hit";
	case EPlayerState::Death: return L"Death";
	case EPlayerState::Jump: return L"Jump";
	case EPlayerState::Fall: return L"Fall";
	case EPlayerState::Dash: return L"Dash";
	case EPlayerState::Crouch: return L"Crouch";
	default: return L"Unknown";
	}
}