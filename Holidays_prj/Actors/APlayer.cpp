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
	bIsMoving = false;

	InputManager& inputManager = InputManager::GetInstance();

	if (inputManager.IsKeyPressed(EKeyState::EKS_A) && bCanJump)
	{
		bCanJump = false;
		bIsJumping = true;
		MyPhysics->SetVelocityY(-JumpSpeed);
	}
	else if (inputManager.IsKeyPressed(EKeyState::EKS_S) && bCanDash)
	{
		bCanDash = false;
		bIsDashing = true;
		// MyPhysics->SetVelocityY(-JumpSpeed);
	}
	else if (inputManager.IsKeyPressed(EKeyState::EKS_Down) && bCanCrouch)
	{
		bCanCrouch = false;
		bIsCrouching = true;
		// MyPhysics->SetVelocityY(-JumpSpeed);
	}

	if (inputManager.IsKeyPressed(EKeyState::EKS_Left))
	{
		MoveDirection.X = -1.0f;
		MyCollider->SetOffset(GetSize().X * 0.05f, GetSize().Y * 0.30f);
		bIsMoving = true;
	}
	if (inputManager.IsKeyPressed(EKeyState::EKS_Right))
	{
		MoveDirection.X = 1.0f;
		MyCollider->SetOffset(-GetSize().X * 0.05f, GetSize().Y * 0.30f);
		bIsMoving = true;
	}

	if (bIsMoving)
	{
		Move(MoveDirection);
	}
	else
	{
		Physics* MyPhysics = GetComponent<Physics>();
		MyPhysics->SetVelocityX(MyPhysics->GetVelocity().X * 0.75f);
	}

	APawn::OnTick(DeltaTime);
}

void APlayer::OnRender(Gdiplus::Graphics* InGraphics)
{
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
		case ETerrainType::None:
			return;
		case ETerrainType::Solid:
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

void APlayer::InitStats()
{
	bCanMove = true;
	bIsMoving = false;
	
	bCanJump = true;
	bIsFloating = false;
}
