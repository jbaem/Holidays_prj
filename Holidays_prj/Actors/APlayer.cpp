#include "APlayer.h"

#include "../Components/Physics.h"
#include "../Components/CircleCollider.h"
#include "../Components/RectangleCollider.h"

#include "../Singletons/InputManager.h"
#include "../Singletons/ResourceManager.h"
#include "ATerrain.h"

void APlayer::OnInitialize()
{
	APawn::OnInitialize();

	SetSize(120.0f, 80.0f);
	IdleSprite = ResourceManager::GetInstance().GetImage(EResourceID::PlayerIdle);
	MoveSprite = ResourceManager::GetInstance().GetImage(EResourceID::PlayerMove);

	SetState(EPlayerState::Idle);
}

void APlayer::OnTick(float DeltaTime)
{

	Physics* MyPhysics = GetComponent<Physics>();
	if (!MyPhysics)
	{
		OutputDebugStringW(L"Error : physic\n");
		return;
	}

	Gdiplus::PointF MoveDirection = { 0.0f, 0.0f };
	bool bIsMoving = false;

	InputManager& inputManager = InputManager::GetInstance();
	if (inputManager.IsKeyPressed(EKeyState::EKS_Left))
	{
		OutputDebugStringW(L"Left key pressed\n");
		MoveDirection.X = -1.0f;
		FacingDirection = EPlayerDirection::Left;
		bIsMoving = true;
	}

	if (inputManager.IsKeyPressed(EKeyState::EKS_Right))
	{
		OutputDebugStringW(L"Right key pressed\n");
		MoveDirection.X = 1.0f;
		FacingDirection = EPlayerDirection::Right;
		bIsMoving = true;
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
	Gdiplus::Bitmap* CurrentSprite = Image;
	if (!CurrentSprite)
		return;

	switch (State)
	{
	case EPlayerState::Idle:
		CurrentSprite = IdleSprite;
		break;
	case EPlayerState::Move:
		CurrentSprite = MoveSprite;
		break;
	}

	if (!CurrentSprite)
		return;

	Gdiplus::GraphicsState originalState = InGraphics->Save();
	InGraphics->TranslateTransform(Position.X, Position.Y);

	if (FacingDirection == EPlayerDirection::Left)
	{
		InGraphics->ScaleTransform(-1.0f, 1.0f);
	}

	Gdiplus::PointF RenderPos = {
		-GetSize().X * GetPivot().X,
		-GetSize().Y * GetPivot().Y
	};

	const float FrameWidth = CurrentSprite->GetWidth() / (float)TotalFrames;
	const float FrameHeight = (float)CurrentSprite->GetHeight();
	float SourceX = CurrentFrameIndex * FrameWidth;

	InGraphics->DrawImage(
		CurrentSprite,
		Gdiplus::RectF(RenderPos.X, RenderPos.Y, GetSize().X, GetSize().Y),
		SourceX, 0, FrameWidth, FrameHeight,
		Gdiplus::UnitPixel
	);
	
	InGraphics->Restore(originalState);


	// --- 입력 상태 디버그 렌더링 ---
	InputManager& inputManager = InputManager::GetInstance();

	// 사용할 폰트와 브러쉬 생성
	Gdiplus::Font debugFont(L"Arial", 12);
	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0));

	// 화면 좌상단에 현재 눌린 키 표시
	if (inputManager.IsKeyPressed(EKeyState::EKS_Left))
	{
		InGraphics->DrawString(L"LEFT", -1, &debugFont, Gdiplus::PointF(10, 10), &blackBrush);
	}
	if (inputManager.IsKeyPressed(EKeyState::EKS_Right))
	{
		InGraphics->DrawString(L"RIGHT", -1, &debugFont, Gdiplus::PointF(10, 30), &blackBrush);
	}
}

void APlayer::OnOverlap(AActor* Other)
{
	if (ATerrain* Terrain = dynamic_cast<ATerrain*>(Other))
	{
		CircleCollider* MyCollider = GetComponent<CircleCollider>();
		RectangleCollider* TerrainCollider = Terrain->GetComponent<RectangleCollider>();

		if (MyCollider && TerrainCollider)
		{
			float MyBottom = GetPosition().Y + MyCollider->GetRadius();
			float TerrainTop = Terrain->GetPosition().Y - TerrainCollider->GetHeight() * 0.5f;
			float overlap = MyBottom - TerrainTop;

			if (overlap > 0)
			{
				Gdiplus::PointF currentPos = GetPosition();
				SetPosition(currentPos.X, currentPos.Y - overlap);
			}
		}

		Physics* MyPhysics = GetComponent<Physics>();
		if (MyPhysics && MyPhysics->GetVelocity().Y > 0)
		{
			MyPhysics->SetVelocityY(0.0f);
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
