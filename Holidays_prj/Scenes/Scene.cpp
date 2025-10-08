#include "Scene.h"

#include "../Singletons/GameManager.h"

void Scene::OnInitialize()
{

}

void Scene::OnDestroy()
{
	for (auto ActorPair : Actors)
	{
		for (AActor* Actor : ActorPair.second)
		{
			delete Actor;
			Actor = nullptr;
		}
		ActorPair.second.clear();
	}
	Actors.clear();
}

void Scene::OnTick(float DeltaTime)
{
	for (const auto& ActorPair : Actors)
	{
		for (AActor* Actor : ActorPair.second)
		{
			Actor->OnTick(DeltaTime);
		}
	}
}

void Scene::OnRender(Gdiplus::Graphics* InGraphics)
{
	for (const auto& ActorPair : Actors)
	{
		for (AActor* Actor : ActorPair.second)
		{
			Actor->OnRender(InGraphics);
		}
	}
}
