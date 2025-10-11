#include "APlayer.h"

#include "../Components/Physics.h"
#include "../Components/CircleCollider.h"
#include "../Components/RectangleCollider.h"

#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"

#include "../Components/PlayerAnimator.h"

#include "ATerrain.h"

class Animator;

void APlayer::OnInitialize()
{
	APawn::OnInitialize();

	SetSize(FrameSize.X * ImageScale, FrameSize.Y * ImageScale);

	Collider* MyCollider = GetComponent<CircleCollider>();
	MyCollider->SetOffset(-GetSize().X * 0.05f, GetSize().Y * 0.30f);
	static_cast<CircleCollider*>(MyCollider)->SetRadius(GetSize().Y * 0.20f);

	MyCollider->SetLayer(EPhysicsLayer::Player);

	AddComponent(new PlayerAnimator(this));
}

void APlayer::OnTick(float DeltaTime)
{
	Physics* MyPhysics = GetComponent<Physics>();
	CircleCollider* MyCollider = GetComponent<CircleCollider>();

	if (!MyPhysics || !MyCollider)
	{
		return;
	}

	InputManager& IM = InputManager::GetInstance();

	if (IM.IsKeyPressed(EKey::EK_JUMP) && bCanJump && bIsOnGround)
	{
		bCanJump = false;
		bIsOnGround = false;
		MyPhysics->SetVelocityY(-JumpSpeed);
	}

	if (IM.IsKeyPressed(EKey::EK_DASH) && bCanDash && bIsOnGround && !bIsCrouching)
	{
		bCanDash = false;
		bIsDashing = true;

		if(Look == ELook::Right)
		{
			MyPhysics->SetVelocityX(DashSpeed);
		}
		else
		{
			MyPhysics->SetVelocityX(-DashSpeed);
		}
		return;
	}

	bIsCrouching = false;
	if(IM.IsKeyPressed(EKey::EK_DOWN) && bCanCrouch && bIsOnGround)
	{
		bIsCrouching = true;
	}
	
	Gdiplus::PointF MoveDirection = { 0.0f, 0.0f };
	bIsMoving = false;
	if(bCanMove && !bIsCrouching && !bIsDashing)
	{
		float RealMoveSpeed = abs(MyPhysics->GetVelocity().X);
		if (RealMoveSpeed < MoveSpeed) RealMoveSpeed = MoveSpeed;

		if (IM.IsKeyPressed(EKey::EK_LEFT))
		{
			MoveDirection.X = -1.0f;
			MyCollider->SetOffset(GetSize().X * 0.05f, GetSize().Y * 0.30f);
			Look = ELook::Left;
			MyPhysics->SetVelocityX(-RealMoveSpeed);
		}
		if (IM.IsKeyPressed(EKey::EK_RIGHT))
		{
			MoveDirection.X = 1.0f;
			MyCollider->SetOffset(-GetSize().X * 0.05f, GetSize().Y * 0.30f);
			Look = ELook::Right;
			MyPhysics->SetVelocityX(RealMoveSpeed);
		}
	}

	if (bIsMoving)
	{
		Move(MoveDirection);
	}
	else
	{
		Physics* MyPhysics = GetComponent<Physics>();
		MyPhysics->SetVelocityX(MyPhysics->GetVelocity().X * 0.75f);
		if (abs(MyPhysics->GetVelocity().X) < 5.0f)
		{
			MyPhysics->SetVelocityX(0.0f);
		}
	}

	APawn::OnTick(DeltaTime);

	bIsOnGround = false;
}

void APlayer::OnRender(Gdiplus::Graphics* InGraphics)
{
	Animator* animator = GetComponent<Animator>();
	if(!animator)
		return;

	Gdiplus::Bitmap* CurrentSprite = animator->GetCurrentSpriteSheet();
	Gdiplus::RectF SourceRect = animator->GetCurrentFrameSourceRect();
	if (!CurrentSprite)
		return;

	Gdiplus::GraphicsState originalState = InGraphics->Save();
	InGraphics->TranslateTransform(Position.X, Position.Y);
	if(Look == ELook::Left)
	{
		InGraphics->ScaleTransform(-1.0f, 1.0f);
	}
	Gdiplus::PointF RenderPos = GetRenderPosition();

	InGraphics->DrawImage(
		CurrentSprite,
		Gdiplus::RectF(
			RenderPos.X - Position.X,
			RenderPos.Y - Position.Y,
			Size.X, Size.Y),
		SourceRect.X, SourceRect.Y, SourceRect.Width, SourceRect.Height,
		Gdiplus::UnitPixel
	);
	
	InGraphics->Restore(originalState);

	APawn::OnRender(InGraphics);
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
		case EBlockType::None:
			return;
		case EBlockType::Solid:
			{
				Gdiplus::PointF MyPos = MyCollider->GetCenter();
				Gdiplus::PointF TerrainPos = TerrainCollider->GetCenter();

				Gdiplus::Rect MyBox(
					MyCollider->GetCenter().X - MyCollider->GetRadius(),
					MyCollider->GetCenter().Y - MyCollider->GetRadius(),
					MyCollider->GetRadius() * 2,
					MyCollider->GetRadius() * 2
				);

				Gdiplus::Rect TerrainBox(
					TerrainCollider->GetCenter().X - TerrainCollider->GetWidth() * 0.5f,
					TerrainCollider->GetCenter().Y - TerrainCollider->GetHeight() * 0.5f,
					TerrainCollider->GetWidth(),
					TerrainCollider->GetHeight()
				);

				float overlap = 0.0f;
				Gdiplus::PointF CurrentPos = GetPosition();
				if (MyBox.GetBottom() > TerrainBox.GetTop() && MyPos.Y < TerrainBox.GetTop()) // above
				{
					overlap = MyBox.GetBottom() - TerrainBox.GetTop();
					SetPosition(CurrentPos.X, CurrentPos.Y - overlap);
					if (MyPhysics->GetVelocity().Y > 0)
					{
						MyPhysics->SetVelocityY(0.0f);
						bIsOnGround = true;
						bCanJump = true;
					}
				}
				else if (MyBox.GetTop() < TerrainBox.GetBottom() && MyPos.Y > TerrainBox.GetBottom()) // below
				{
					overlap = TerrainBox.GetBottom() - MyBox.GetTop();
					SetPosition(CurrentPos.X, CurrentPos.Y + overlap);
					if (MyPhysics->GetVelocity().Y < 0)
					{
						MyPhysics->SetVelocityY(0.0f);
					}
				}
				else
				{
					if(MyBox.GetRight() > TerrainBox.GetLeft() && MyPos.X < TerrainBox.GetLeft()) // left side
					{
						overlap = MyBox.GetRight() - TerrainBox.GetLeft();
						SetPosition(CurrentPos.X - overlap, CurrentPos.Y);
						if(MyPhysics->GetVelocity().X > 0)
						{
							MyPhysics->SetVelocityX(0.0f);
						}
					}
					else if(MyBox.GetLeft() < TerrainBox.GetRight() && MyPos.X > TerrainBox.GetRight()) // right side
					{
						overlap = TerrainBox.GetRight() - MyBox.GetLeft();
						SetPosition(CurrentPos.X + overlap, CurrentPos.Y);
						if(MyPhysics->GetVelocity().X < 0)
						{
							MyPhysics->SetVelocityX(0.0f);
						}
					}
				}
			}
			break;
		case EBlockType::OneWay:
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
					bIsOnGround = true;
					bCanJump = true;
				}
			}
			break;
		}
	}
}
