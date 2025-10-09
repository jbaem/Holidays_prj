#include "Scene.h"

#include "../Managers/GameManager.h"
#include "../Components/Collider.h"

Scene::~Scene()
{
	OnExit();
}

void Scene::OnEnter()
{
	MainPlayer = GameManager::GetInstance().GetMainPlayer();
	ActorsMap[ERenderLayer::Player].insert(MainPlayer);
	MainPlayer->SetOwnerScene(this);
}

void Scene::OnExit()
{
	for (auto ActorPair : ActorsMap)
	{
		if (ActorPair.first == ERenderLayer::Player)
			continue;

		for (AActor* Actor : ActorPair.second)
		{
			delete Actor;
			Actor = nullptr;
		}
		ActorPair.second.clear();
	}
	ActorsMap.clear();
	PendingDestroyActors.clear();
}

void Scene::OnTick(float DeltaTime)
{
	for (const auto& ActorPair : ActorsMap)
	{
		for (AActor* Actor : ActorPair.second)
		{
			if (Actor->IsPendingDestroy())
				continue;

			Actor->OnTick(DeltaTime);
		}
	}

	ProcessCollisions();
	ProcessPendingDestroyActors();
}

void Scene::OnRender(Gdiplus::Graphics* InGraphics)
{
	for (const auto& ActorPair : ActorsMap)
	{
		for (AActor* Actor : ActorPair.second)
		{
			Actor->OnRender(InGraphics);
		}
	}
}

void Scene::RegisterActor(AActor* InActor)
{
	if (!InActor)
		return;

	ActorsMap[InActor->GetLayer()].insert(InActor);
	InActor->SetOwnerScene(this);
}

void Scene::DeregisterActor(AActor* InActor)
{
	if (!InActor)
		return;

	ActorsMap[InActor->GetLayer()].erase(InActor);
}

void Scene::ProcessPendingDestroyActors()
{
	for (AActor* Actor : PendingDestroyActors)
	{
		if (!Actor)
			return;

		DeregisterActor(Actor);
		delete Actor;
	}
	PendingDestroyActors.clear();
}


void Scene::ProcessCollisions()
{
	UpdateActorCache();

	for (int i = 0; i < CollidableActorsCache.size(); ++i)
	{
		for (int j = i + 1; j < CollidableActorsCache.size(); ++j)
		{
			AActor* ActorA = CollidableActorsCache[i];
			AActor* ActorB = CollidableActorsCache[j];
			if (!ActorA || !ActorB)
				continue;

			Collider* ColliderA = ActorA->GetComponent<Collider>();
			Collider* ColliderB = ActorB->GetComponent<Collider>();
			if (!ColliderA || !ColliderB)
				continue;
		
			if (CollisionManager::GetInstance()
				.ShouldCollision(ColliderA->GetLayer(), ColliderB->GetLayer())
				&& ColliderA->IsCollision(ColliderB))
			{
				ActorA->OnOverlap(ActorB);
				ActorB->OnOverlap(ActorA);
			}
		}
	}
}

void Scene::UpdateActorCache()
{
	CollidableActorsCache.clear();

	size_t totalActors = 0;
	for (const auto& pair : ActorsMap) totalActors += pair.second.size();
	CollidableActorsCache.reserve(totalActors);

	for (const auto& pair : ActorsMap)
	{
		for (AActor* Actor : pair.second)
		{
			if (!Actor || Actor->IsPendingDestroy())
				continue;

			CollidableActorsCache.push_back(Actor);
		}
	}
}
