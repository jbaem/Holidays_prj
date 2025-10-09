#include "GameManager.h"
#include "../Components/Collider.h"

#include "Factory.h"
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
			L"Fail to Create Back Buffer",
			L"ERROR",
			MB_OK | MB_ICONERROR
		);
	}
	
	MainPlayer = Factory::GetInstance().SpawnActor<APlayer>(EResourceID::PlayerMove, ERenderLayer::Player);
	MainSceneHandler = new SceneHandler();

#ifdef TEST:
	State = GameState::PlayerTest;
#else
	State = GameState::MainMenu;
#endif
}

void GameManager::Destroy()
{
	delete MainSceneHandler;
	MainSceneHandler = nullptr;

	delete MainPlayer;
	MainPlayer = nullptr;

	delete BackBufferGraphics;
	BackBufferGraphics = nullptr;
	delete BackBuffer;
	BackBuffer = nullptr;
}

void GameManager::Tick(float DeltaTime)
{
	if (State == GameState::Playing || State == GameState::PlayerTest)
	{
		MainSceneHandler->Tick(DeltaTime);
	}
}

void GameManager::Render()
{
	if (!BackBufferGraphics)
		return;

	BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));
	MainSceneHandler->Render(BackBufferGraphics);
}

void GameManager::SetGameState(GameState InState)
{
	State = InState;
}
