#include "GameManager.h"
#include "../Components/Collider.h"

#include "Factory.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

#define TEST // TODO : should change to comment

void GameManager::Initialize()
{
	BackBuffer = new Gdiplus::Bitmap(ScreenWidth, ScreenHeight, PixelFormat32bppARGB);
	BackBufferGraphics = Gdiplus::Graphics::FromImage(BackBuffer);
	if (!BackBuffer || !BackBufferGraphics)
	{
		MessageBox (
			hMainWindow,
			L"백 버퍼, 그래픽스 생성 실패",
			L"오류",
			MB_OK | MB_ICONERROR
		);
	}

	InputManager::GetInstance().Initialize();
	CollisionManager::GetInstance().Initialize();
	ResourceManager::GetInstance().Initialize();

#ifdef TEST:
	State = GameState::PlayerTest;
#else
	State = GameState::MainMenu;
#endif
}

void GameManager::Destroy()
{
	delete MainPlayer;
	MainPlayer = nullptr;

	ResourceManager::GetInstance().Destroy();
	CollisionManager::GetInstance().Destroy();
	InputManager::GetInstance().Destroy();

	delete BackBufferGraphics;
	BackBufferGraphics = nullptr;
	delete BackBuffer;
	BackBuffer = nullptr;
}

void GameManager::Tick(float DeltaTime)
{
	if (State == GameState::Playing || State == GameState::PlayerTest)
	{
		SceneManager::GetInstance().Tick(DeltaTime);

		ProcessCollisions();
		ProcessPendingDestroyActors();
	}
}

void GameManager::Render()
{
	if (!BackBufferGraphics)
		return;

	BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));
	SceneManager::GetInstance().Render(BackBufferGraphics);
}

void GameManager::RegisterActor(AActor* InActor)
{
	if (!InActor || Actors.find(InActor) != Actors.end())
		return;
	Actors.insert(InActor);
}

// TODO: SetMainPlayer()
void GameManager::SetMainPlayer()
{
	if (MainPlayer == nullptr)
		MainPlayer = Factory::GetInstance().SpawnActor<APlayer>(EResourceID::PlayerMove, ERenderLayer::Player);
}

void GameManager::DeregisterActor(AActor* InActor)
{
	if (!InActor || Actors.find(InActor) == Actors.end())
		return;
	Actors.erase(InActor);
}

void GameManager::ProcessCollisions()
{
	for (auto it_a = Actors.begin(); it_a != Actors.end(); ++it_a)
	{
		for (auto it_b = std::next(it_a); it_b != Actors.end(); ++it_b)
		{
			AActor* A = *it_a;
			AActor* B = *it_b;
			if (!A || !B)
				continue;

			Collider* ColliderA = A->GetComponent<Collider>();
			Collider* ColliderB = B->GetComponent<Collider>();
			if (!ColliderA || !ColliderB)
				continue;

			if (CollisionManager::GetInstance()
				.ShouldCollision(
					ColliderA->GetLayer(),
					ColliderB->GetLayer()
				))
			{
				A->OnOverlap(B);
				B->OnOverlap(A);
			}
		}
	}
}

void GameManager::ProcessPendingDestroyActors()
{
	for (AActor* Actor : PendingDestroyActors)
	{
		if (!Actor)
			return;

		DeregisterActor(Actor);
		Actor->Destroy();
		delete Actor;
	}
	PendingDestroyActors.clear();
}
