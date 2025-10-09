#pragma once

#include "../Common.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

#include "../Actors/AActor.h"
#include "../Actors/APlayer.h"
#include "../Actors/ABackground.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	virtual void OnEnter();
	virtual void OnExit();

	virtual void OnTick(float DeltaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);

	void RegisterActor(AActor* InActor);
	inline void RequestDestroy(AActor* Target) { 
		PendingDestroyActors.push_back(Target); 
	}

	// Getter
	const std::wstring& GetName() const { return Name; }

protected:
	void DeregisterActor(AActor* InActor);
	void ProcessPendingDestroyActors();
	void ProcessCollisions();
	void UpdateActorCache();

	std::wstring Name = L"";

	std::map<ERenderLayer, std::unordered_set<AActor*>> ActorsMap;
	std::vector<AActor*> PendingDestroyActors;
	std::vector<AActor*> CollidableActorsCache;

	APlayer* MainPlayer = nullptr;
};

