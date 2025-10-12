#include "APlayer.h"

#include "../Components/Physics.h"
#include "../Components/CircleCollider.h"
#include "../Components/RectangleCollider.h"

#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/Factory.h"

#include "../Components/PlayerAnimator.h"

#include "ATerrain.h"
#include "APlayerBullet.h"

class Animator;

void APlayer::OnInitialize()
{
	APawn::OnInitialize();

	MaxHealth = 50.0f;
	Health = 50.0f;

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
		PlayerAnimator* animator = GetComponent<PlayerAnimator>();
		if (animator)
			animator->SetState(EPlayerState::Dash);

		return;
	}

	bIsCrouching = false;
	if(IM.IsKeyPressed(EKey::EK_DOWN) && bCanCrouch && bIsOnGround)
	{
		bIsCrouching = true;
	}

	if (IM.IsKeyPressed(EKey::EK_SHOOT) && !bIsCrouching && !bIsDashing && bCanShoot)
	{
		bCanShoot = false;
		
		Gdiplus::PointF BulletSpawnPos = { 0.0f, 0.0f };
		if (Look == ELook::Right)
		{
			BulletSpawnPos = { Position.X + 40.0f, Position.Y + 20.0f };
		}
		else
		{
			BulletSpawnPos = { Position.X - 40.0f, Position.Y + 20.0f };
		}

		APlayerBullet* NewBullet = Factory::GetInstance().SpawnActor<APlayerBullet>(EResourceID::PlayerBullet, ERenderLayer::Bullet);
		if (NewBullet)
			NewBullet->SetPosition(BulletSpawnPos); 

		NewBullet->SetDirection(Look == ELook::Right ? Gdiplus::PointF{ 1.0f, 0.0f } : Gdiplus::PointF{ -1.0f, 0.0f });
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

	float FallingThreshold = 20.0f;

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
				if (MyBox.GetBottom() > TerrainBox.GetTop() && MyPos.Y < TerrainBox.GetTop() + FallingThreshold) // above // Falling Error Margin
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

				if (MyPhysics->GetVelocity().Y > 0 && PlayerBottom <= TerrainTop + FallingThreshold) // Falling Error Margin
				{
					float overlap = PlayerBottom - TerrainTop;
					Gdiplus::PointF currentPos = GetPosition();
					SetPosition(currentPos.X, currentPos.Y - overlap);

					MyPhysics->SetVelocityY(0.0f);
					bIsOnGround = true;
					bCanJump = true;
				}
			}
			break;
		}
	}
}

void APlayer::TakeDamage(float InDamage)
{
	Health -= InDamage;
	if (Health < 0.01f)
	{
		GameManager::GetInstance().SetGameState(GameState::GameOver);
	}

	State = EPlayerState::Hit;

	Physics* MyPhysics = GetComponent<Physics>();
	if (MyPhysics)
	{
		MyPhysics->SetVelocityX(
			Look == ELook::Right ? -400.0f : 400.0f
		);
		MyPhysics->SetVelocityY(-100.0f);
	}
}
