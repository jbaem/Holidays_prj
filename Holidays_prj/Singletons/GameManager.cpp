#include "GameManager.h"

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

	// TODO: Spawn Actors
}

void GameManager::Destroy()
{


	delete BackBufferGraphics;
	BackBufferGraphics = nullptr;
	delete BackBuffer;
	BackBuffer = nullptr;
}

void GameManager::Tick(float deltaTime)
{
	if (State == GameState::Playing)
	{
		// TODO: All Actors->OnTick

		// TODO: Process Collsion, Destroy Actors
	}
}

void GameManager::Render()
{
	if (!BackBufferGraphics)
		return;

	BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));
	
	// TODO: All Actors->OnRender
}
