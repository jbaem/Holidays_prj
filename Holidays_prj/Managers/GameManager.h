#pragma once

#include <unordered_set>

#include "../Common.h"

#include "TSingleton.h"
#include "SceneHandler.h"
#include "CollisionManager.h"

#include "../Actors/APlayer.h"

class GameManager : public TSingleton<GameManager>
{
	friend class TSingleton<GameManager>;
public:
	virtual void Initialize();
	virtual void Destroy();

	void Tick(float DeltaTime);
	void Render();
	
	void RequestDestroy(AActor* InActor);

	static constexpr unsigned int ScreenWidth = 1208;
	static constexpr unsigned int ScreenHeight = 720;
	static constexpr unsigned int ActorDefaultSize = 64;

	// Getter
	inline HWND GetWindowHandle() const { return hMainWindow; }
	inline const Gdiplus::Point& GetAppPosition() const { return AppPosition; }
	inline Gdiplus::Bitmap* GetBackBuffer() { return BackBuffer; };
	inline APlayer* GetMainPlayer() { return MainPlayer; }

	// Setter
	inline void SetWindowHandle(HWND InHWnd)
	{
		if (hMainWindow == nullptr)
			hMainWindow = InHWnd;
	}
	void SetGameState(GameState InState);

private:
	virtual ~GameManager() = default;

	HWND hMainWindow = nullptr;
	Gdiplus::Point AppPosition = Gdiplus::Point(50, 50);
	
	Gdiplus::Bitmap* BackBuffer = nullptr;
	Gdiplus::Graphics* BackBufferGraphics = nullptr;

	APlayer* MainPlayer = nullptr;
	SceneHandler* MainSceneHandler = nullptr;
	
	GameState State = GameState::Playing;
};

