#pragma once

#include "../Common.h"

#include "TSingleton.h"
#include "../Actors/APlayer.h"
#include <unordered_set>
#include "../Components/Physics.h"
#include <set>

class GameManager : public TSingleton<GameManager>
{
	friend class TSingleton<GameManager>;
public:
	void Initialize();
	void Destroy();
	void Tick(float DeltaTime);
	void Render();

	void RegisterActor(ERenderLayer InLayer, AActor* InActor);
	inline void RequestDestroy(AActor* Target) { PendingDestroyActors.push_back(Target); }

	static constexpr unsigned int ScreenWidth = 1208;
	static constexpr unsigned int ScreenHeight = 720;
	static constexpr unsigned int ActorDefaultSize = 64;

	// Getter
	inline HWND GetWindowHandle() const { return hMainWindow; }
	inline const Gdiplus::Point& GetAppPosition() const { return AppPosition; }
	inline Gdiplus::Bitmap* GetBackBuffer() { return BackBuffer; };

	// Setter
	inline void SetWindowHandle(HWND InHWnd)
	{
		if (hMainWindow == nullptr)
			hMainWindow = InHWnd;
	}
	inline void SetGameState(GameState InState) {}

private:
	GameManager() = default;
	virtual ~GameManager() = default;

	void DeregisterActor(AActor* InActor);
	void ProcessCollisions();
	void ProcessPendingDestroyActors();

	std::unordered_map<ERenderLayer, std::set<AActor*>> ActorMap;
	std::vector<AActor*> PendingDestroyActors;
	std::unordered_map<EPhysicsLayer, std::vector<Physics*>> PhysicsComponents;

	HWND hMainWindow = nullptr;
	Gdiplus::Point AppPosition = Gdiplus::Point(50, 50);
	Gdiplus::Bitmap* BackBuffer = nullptr;
	Gdiplus::Graphics* BackBufferGraphics = nullptr;

	APlayer* MainPlayer = nullptr;
	

	GameState State = GameState::Playing;
};

