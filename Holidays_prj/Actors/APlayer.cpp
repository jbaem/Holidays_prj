#include "APlayer.h"

#include "../Components/Physics.h"
#include "../Components/CircleCollider.h"
#include "../Components/RectangleCollider.h"

#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "ATerrain.h"

void APlayer::OnInitialize()
{
	SetSize(FrameSize.X * ImageScale, FrameSize.Y * ImageScale);

	APawn::OnInitialize();
	Collider* MyCollider = GetComponent<CircleCollider>();
	MyCollider->SetOffset(-GetSize().X * 0.05f, GetSize().Y * 0.30f);
	static_cast<CircleCollider*>(MyCollider)->SetRadius(GetSize().Y * 0.20f);
	MyCollider->SetLayer(EPhysicsLayer::Player);

	IdleSprite = ResourceManager::GetInstance().GetImage(EResourceID::PlayerIdle);
	MoveSprite = ResourceManager::GetInstance().GetImage(EResourceID::PlayerMove);

	SetState(EPlayerState::Idle);
}

void APlayer::OnTick(float DeltaTime)
{
	Physics* MyPhysics = GetComponent<Physics>();
	CircleCollider* MyCollider = GetComponent<CircleCollider>();

	if (!MyPhysics || !MyCollider)
	{
		return;
	}

	Gdiplus::PointF MoveDirection = { 0.0f, 0.0f };
	bool bIsMoving = false;

	InputManager& inputManager = InputManager::GetInstance();
	if (inputManager.IsKeyPressed(EKeyState::EKS_Left))
	{
		MoveDirection.X = -1.0f;
		FacingDirection = EPlayerDirection::Left;
		MyCollider->SetOffset(GetSize().X * 0.05f, GetSize().Y * 0.30f);
		bIsMoving = true;
	}

	if (inputManager.IsKeyPressed(EKeyState::EKS_Right))
	{
		MoveDirection.X = 1.0f;
		FacingDirection = EPlayerDirection::Right;
		MyCollider->SetOffset(-GetSize().X * 0.05f, GetSize().Y * 0.30f);
		bIsMoving = true;
	}

	if(inputManager.IsKeyPressed(EKeyState::EKS_A) && bCanJump)
	{
		bCanJump = false;
		State = EPlayerState::Jump;
		MyPhysics->SetVelocityY(-JumpSpeed);
	}

	SetState(bIsMoving ? EPlayerState::Move : EPlayerState::Idle);
	if (bIsMoving)
	{
		Move(MoveDirection);
	}
	else
	{
		Physics* MyPhysics = GetComponent<Physics>();
		MyPhysics->SetVelocityX(MyPhysics->GetVelocity().X * 0.75f);
	}

	UpdateAnimation(DeltaTime);
	APawn::OnTick(DeltaTime);
}

void APlayer::OnRender(Gdiplus::Graphics* InGraphics)
{
	APawn::OnRender(InGraphics);

	Gdiplus::Bitmap* CurrentSprite = nullptr;
	switch (State)
	{
	case EPlayerState::Idle: CurrentSprite = IdleSprite; break;
	case EPlayerState::Move: CurrentSprite = MoveSprite; break;
	}
	if (!CurrentSprite) 
		return;

	Gdiplus::GraphicsState originalState = InGraphics->Save();
	InGraphics->TranslateTransform(Position.X, Position.Y);

	if (FacingDirection == EPlayerDirection::Left)
	{
		InGraphics->ScaleTransform(-1.0f, 1.0f);
	}

	Gdiplus::PointF RenderPos = GetRenderPosition();

	const float FrameWidth = CurrentSprite->GetWidth() / (float)TotalFrames;
	const float FrameHeight = (float)CurrentSprite->GetHeight();
	float SourceX = CurrentFrameIndex * FrameWidth;

	InGraphics->DrawImage(
		CurrentSprite,
		Gdiplus::RectF(
			RenderPos.X - Position.X, 
			RenderPos.Y - Position.Y,
			GetSize().X, GetSize().Y),
		SourceX, 0, FrameWidth, FrameHeight,
		Gdiplus::UnitPixel
	);
	
	InGraphics->Restore(originalState);
}

void APlayer::OnOverlap(AActor* Other)
{
	Physics* MyPhysics = GetComponent<Physics>();
	CircleCollider* MyCollider = GetComponent<CircleCollider>();

	if (ATerrain* Terrain = dynamic_cast<ATerrain*>(Other))
	{
		RectangleCollider* TerrainCollider = Terrain->GetComponent<RectangleCollider>();
		if(!MyPhysics || !MyCollider || !TerrainCollider)
			return;

		switch (Terrain->GetTerrainType())
		{
		case ETerrainType::None:
			return;
		case ETerrainType::Solid:
			{
				float PlayerBottom = MyCollider->GetCenter().Y + MyCollider->GetRadius();
				float TerrainTop = TerrainCollider->GetCenter().Y - TerrainCollider->GetHeight() / 2.f;
				float overlap = PlayerBottom - TerrainTop;

				if (overlap > 0)
				{
					Gdiplus::PointF currentPos = GetPosition();
					SetPosition(currentPos.X, currentPos.Y - overlap);
					if (MyPhysics->GetVelocity().Y > 0)
					{
						MyPhysics->SetVelocityY(0.0f);
						bCanJump = true;
					}
				}
			}
			break;
		case ETerrainType::OneWay:
			{
				float PlayerBottom = MyCollider->GetCenter().Y + MyCollider->GetRadius();
				float TerrainTop = TerrainCollider->GetCenter().Y - TerrainCollider->GetHeight() / 2.f;

				if (MyPhysics->GetVelocity().Y > 0 && PlayerBottom <= TerrainTop + 10.0f) // +10은 약간의 오차 허용
				{
					// 겹친 만큼 플레이어를 위로 밀어냄 (지형 위에 서도록)
					float overlap = PlayerBottom - TerrainTop;
					Gdiplus::PointF currentPos = GetPosition();
					SetPosition(currentPos.X, currentPos.Y - overlap);

					// 땅에 닿았으므로 Y축 속도를 0으로 리셋
					MyPhysics->SetVelocityY(0.0f);
					bCanJump = true;
				}
			}
			break;
		}
	}
}

void APlayer::SetState(EPlayerState InState)
{
	if (State == InState)
		return;

	State = InState;
	CurrentFrameIndex = 0;
	AnimationTimer = 0.0f;

	switch (State)
	{
	case EPlayerState::Idle:
		TotalFrames = 10;
		TimePerFrame = 1.0f / 15.0f;
		break;
	case EPlayerState::Move:
		TotalFrames = 10;
		TimePerFrame = 1.0f / 20.0f;
		break;
	}

}

void APlayer::UpdateAnimation(float DeltaTime)
{
	AnimationTimer += DeltaTime;
	if (AnimationTimer >= TimePerFrame)
	{
		AnimationTimer -= TimePerFrame;
		CurrentFrameIndex = (CurrentFrameIndex + 1) % TotalFrames;
	}

}
