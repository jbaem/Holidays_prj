#include "PlayerAnimator.h"

#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "Physics.h"

void PlayerAnimator::OnInitialize()
{
	SpritesMap[EPlayerState::Idle] = ResourceManager::GetInstance().GetImage(EPlayerState::Idle);
	SpritesMap[EPlayerState::Move] = ResourceManager::GetInstance().GetImage(EPlayerState::Move);

	State = EPlayerState::Idle;

	Animator::OnInitialize();
}

void PlayerAnimator::OnTick(float DeltaTime)
{

	FacingDirection = Owner->GetComponent<Physics>()->GetVelocity().X >= 0 ?
		EPlayerDirection::Right :
		EPlayerDirection::Left;

	UpdateAnimation();
	bIsFinished = CurrentAnimation.Update(DeltaTime);
}

void PlayerAnimator::UpdateAnimation()
{
	Gdiplus::PointF& Velocity = Owner->GetComponent<Physics>()->GetVelocity();
	Gdiplus::PointF& Acceleration = Owner->GetComponent<Physics>()->GetAcceleration();
	APlayer* Player = static_cast<APlayer*>(Owner);

	InputManager& IM = InputManager::GetInstance();

	if (Player->bIsJumping)
	{
		if (Velocity.Y > 0)
			SetState(EPlayerState::Fall);
		else
			SetState(EPlayerState::Jump);
		return;
	}

	if (Player->bIsDashing)
	{
		SetState(EPlayerState::Dash);
		
		if (bIsFinished)
			SetState(EPlayerState::Idle);
		
		return;
	}

	if (Player->bIsCrouching)
	{
		SetState(EPlayerState::Crouch);
		
		if(!IM.IsKeyPressed(EKeyState::EKS_Down))
			SetState(EPlayerState::Idle);
		
		return;
	}

	switch (State)
	{
	case EPlayerState::Move:
		if(Velocity.X * Acceleration.X < 0)
			SetState(EPlayerState::Turn);
		break;

	case EPlayerState::Turn:
		if (bIsFinished)
			SetState(EPlayerState::Idle);
		break;

	case EPlayerState::Fall:
		if(Velocity.Y == 0)
			SetState(EPlayerState::Idle);
		break;

	case EPlayerState::Attack1:
		break;

	case EPlayerState::Attack2:
		break;

	case EPlayerState::Hit:
		if (Player->GetHealth() <= 0)
		{
			SetState(EPlayerState::Death);
		}
		break;

	case EPlayerState::Death:
		break;

	// Not used states : Slide
	// Not used states : Wall interactions
	default:
		SetState(EPlayerState::Idle);
		break;
	}
}


void PlayerAnimator::OnRender(Gdiplus::Graphics* InGraphics)
{
	Gdiplus::Bitmap* CurrentSprite = SpritesMap[State];
	if (!CurrentSprite)
		return;

	Gdiplus::GraphicsState originalState = InGraphics->Save();
	InGraphics->TranslateTransform(Owner->GetPosition().X, Owner->GetPosition().Y);
	if (FacingDirection == EPlayerDirection::Left)
	{
		InGraphics->ScaleTransform(-1.0f, 1.0f);
	}
	Gdiplus::PointF RenderPos = Owner->GetRenderPosition();
	const float FrameWidth = CurrentSprite->GetWidth() / (float)CurrentAnimation.TotalFrames;
	const float FrameHeight = (float)CurrentSprite->GetHeight();
	float SourceX = CurrentAnimation.CurrentFrameIndex * FrameWidth;

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
}


void PlayerAnimator::SetState(EPlayerState InState)
{
	if(State == InState)
		return;

	State = InState;
	
	switch (State)
	{
	case EPlayerState::Idle:
		CurrentAnimation.SetAnimation(10, 1.0f / 15.0f, true);
		break;
	case EPlayerState::Move:
		CurrentAnimation.SetAnimation(10, 1.0f / 20.0f, true);
		break;
	}
}