#include "Scene.h"

#include "../Singletons/GameManager.h"

Scene::~Scene()
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

void Scene::OnEnter()
{
}

void Scene::OnExit()
{
}

void Scene::Tick(float DeltaTime)
{
	for (const auto& ActorPair : Actors)
	{
		for (AActor* Actor : ActorPair.second)
		{
			Actor->OnTick(DeltaTime);
		}
	}
}

void Scene::Render(Gdiplus::Graphics* InGraphics)
{
	for (const auto& ActorPair : Actors)
	{
		for (AActor* Actor : ActorPair.second)
		{
			Actor->OnRender(InGraphics);
		}
	}
}
