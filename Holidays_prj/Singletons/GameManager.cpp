#include "GameManager.h"
#include "Factory.h"
#include "../Components/Collider.h"

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

	MainPlayer = Factory::GetInstance().SpawnActor<APlayer>(EResourceID::PlayerIdle, ERenderLayer::Player);
	int idx = 0;
}

void GameManager::Destroy()
{


	delete BackBufferGraphics;
	BackBufferGraphics = nullptr;
	delete BackBuffer;
	BackBuffer = nullptr;
}

void GameManager::Tick(float DeltaTime)
{
	if (State == GameState::Playing)
	{
		for (const auto& ActorPair : ActorMap)
		{
			for (AActor* Actor : ActorPair.second)
			{
				if (!Actor)
					continue;
				Actor->OnTick(DeltaTime);
			}
		}

		ProcessCollisions();
		ProcessPendingDestroyActors();
	}
}

void GameManager::Render()
{
	if (!BackBufferGraphics)
		return;

	BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));
	
	for (const auto& ActorPair : ActorMap)
	{
		for (AActor* Actor : ActorPair.second)
		{
			if (!Actor)
				continue;
			Actor->OnRender(BackBufferGraphics);
		}
	}
}

void GameManager::RegisterActor(ERenderLayer InLayer, AActor* InActor)
{
	if (!InActor)
		return;

	ActorMap[InLayer].insert(InActor);

	Physics* PhysicsComponent = InActor->GetComponent<Physics>();
	// TODO: Physics Layer Logic
}

void GameManager::DeregisterActor(AActor* InActor)
{
	if (!InActor)
		return;

	auto& ActorSet = ActorMap[InActor->GetLayer()];
	if (ActorSet.find(InActor) == ActorSet.end())
		return;



	ActorSet.erase(InActor);
}

void GameManager::ProcessCollisions()
{

}

void GameManager::ProcessPendingDestroyActors()
{
	for (AActor* Actor : PendingDestroyActors)
	{
		if (!Actor)
			return;

		if (Actor == MainPlayer)
			MainPlayer = nullptr;

		DeregisterActor(Actor);
		Actor->OnDestroy();
		delete Actor;
	}
	PendingDestroyActors.clear();
}
