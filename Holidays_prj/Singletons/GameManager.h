#pragma once

#include "../Common.h"

#include "TSingleton.h"

class GameManager : public TSingleton<GameManager>
{
	friend class TSingleton<GameManager>;
public:
	virtual void Initialize();
	virtual void Destroy();
	void Tick(float deltaTime);
	void Render();

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

	HWND hMainWindow = nullptr;
	Gdiplus::Point AppPosition = Gdiplus::Point(50, 50);
	
	Gdiplus::Bitmap* BackBuffer = nullptr;
	Gdiplus::Graphics* BackBufferGraphics = nullptr;

	GameState State = GameState::Playing;
};

