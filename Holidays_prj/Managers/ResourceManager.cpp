#include "ResourceManager.h"

#include "GameManager.h"

void ResourceManager::Initialize()
{
	LoadResources();
	LoadPlayerResources();
}

void ResourceManager::Destroy()
{
	for (auto& Resource : Resources)
	{
		delete Resource.second;
		Resource.second = nullptr;
	}
	Resources.clear();

	for (auto& Resource : PlayerResources)
	{
		delete Resource.second;
		Resource.second = nullptr;
	}
	PlayerResources.clear();

	TileMapping.clear();
}

Gdiplus::Bitmap* ResourceManager::GetImage(EResourceID InID)
{
	if (Resources.find(InID) == Resources.end())
		return nullptr;

	return Resources[InID];
}

Gdiplus::Bitmap* ResourceManager::GetImage(EPlayerState InState)
{
	if (PlayerResources.find(InState) == PlayerResources.end())
		return nullptr;

	return PlayerResources[InState];
}



void ResourceManager::LoadResources()
{
	Resources[EResourceID::None] = nullptr;
	LoadResourceFromFile(EResourceID::BackGround1, L"./Images/Tile/BG1.png");
	LoadResourceFromFile(EResourceID::BackGround2, L"./Images/Tile/BG2.png");
	LoadResourceFromFile(EResourceID::BackGround3, L"./Images/Tile/BG3.png");
	CreateCompositeBackground();

	LoadResourceFromFile(EResourceID::Tileset, L"./Images/Tile/Tileset.png");
	LoadResourceFromFile(EResourceID::Decors, L"./Images/Tile/Decors.png");
	TilePositionMapInit();
}

void ResourceManager::LoadPlayerResources()
{
	LoadResourceFromFile(EPlayerState::Idle, L"./Images/Player/_Idle.png");
	LoadResourceFromFile(EPlayerState::Move, L"./Images/Player/_Run.png");
	LoadResourceFromFile(EPlayerState::Crouch, L"./Images/Player/_Crouch.png");

	LoadResourceFromFile(EPlayerState::Dash, L"./Images/Player/_Roll.png");
	LoadResourceFromFile(EPlayerState::Jump, L"./Images/Player/_Jump.png");
	LoadResourceFromFile(EPlayerState::Fall, L"./Images/Player/_Fall.png");

	LoadResourceFromFile(EPlayerState::Attack1, L"./Images/Player/_Attack1.png");
	LoadResourceFromFile(EPlayerState::Attack2, L"./Images/Player/_Attack2.png");
	LoadResourceFromFile(EPlayerState::Hit, L"./Images/Player/_Hit.png");
	LoadResourceFromFile(EPlayerState::Death, L"./Images/Player/_Death.png");
}

bool ResourceManager::LoadResourceFromFile(EResourceID InID, const wchar_t* InPath)
{
	if (!InPath)
		return false;

	Gdiplus::Bitmap* LoadedImage = new Gdiplus::Bitmap(InPath);
	if (LoadedImage->GetLastStatus() == Gdiplus::Ok)
	{
		Resources[InID] = LoadedImage;
		return true;
	}

	// Fail to Load Image
	delete LoadedImage;
	LoadedImage = nullptr;

	OutputDebugString(L"Fail to Load Resource Image\n");
	MessageBox (
		GameManager::GetInstance().GetWindowHandle(),
		L"Fail to Load Image",
		L"ERROR",
		MB_OK | MB_ICONERROR
	);
	return false;
}

bool ResourceManager::LoadResourceFromFile(EPlayerState InState, const wchar_t* InPath)
{
	if (!InPath)
		return false;

	Gdiplus::Bitmap* LoadedImage = new Gdiplus::Bitmap(InPath);
	if (LoadedImage->GetLastStatus() == Gdiplus::Ok)
	{
		PlayerResources[InState] = LoadedImage;
		return true;
	}

	// Fail to Load Image
	delete LoadedImage;
	LoadedImage = nullptr;

	OutputDebugString(L"Fail to Load Player Image\n");
	MessageBox(
		GameManager::GetInstance().GetWindowHandle(),
		L"Fail to Load Image",
		L"ERROR",
		MB_OK | MB_ICONERROR
	);
	return false;
}

bool ResourceManager::CreateCompositeBackground()
{
	Gdiplus::Bitmap* bg1 = Resources[EResourceID::BackGround1];
	Gdiplus::Bitmap* bg2 = Resources[EResourceID::BackGround2];
	Gdiplus::Bitmap* bg3 = Resources[EResourceID::BackGround3];

	if (bg1->GetLastStatus() != Gdiplus::Ok ||
		bg2->GetLastStatus() != Gdiplus::Ok ||
		bg3->GetLastStatus() != Gdiplus::Ok)
	{
		OutputDebugString(L"Fail to Load Background\n");
		return false;
	}

	UINT Width = bg1->GetWidth();
	UINT Height = bg1->GetHeight();
	Gdiplus::Bitmap* CompositeImage = new Gdiplus::Bitmap(Width, Height, PixelFormat32bppARGB);
	Gdiplus::Graphics* TempGraphics = Gdiplus::Graphics::FromImage(CompositeImage);

	TempGraphics->DrawImage(bg1, 0, 0, Width, Height);
	TempGraphics->DrawImage(bg2, 0, 0, Width, Height);
	TempGraphics->DrawImage(bg3, 0, 0, Width, Height);

	Resources[EResourceID::BackGround] = CompositeImage;

	delete TempGraphics;
	return true;
}

void ResourceManager::TilePositionMapInit()
{
	TileMapping[EResourceID::LeftPlatform] = { {0.0f, 0.0f}, {24.0f, 48.0f} };
	TileMapping[EResourceID::MiddlePlatform] = { {12.0f, 0.0f}, {24.0f, 48.0f} };
	TileMapping[EResourceID::RightPlatform] = { {24.0f, 0.0f}, {24.0f, 48.0f} };
	
	TileMapping[EResourceID::LeftWall] = { {0.0f, 60.0f}, {24.0f, 24.0f} };
	TileMapping[EResourceID::RightWall] = { {24.0f, 60.0f}, {24.0f, 24.0f} };
	TileMapping[EResourceID::TopWall] = { {12.0f, 72.0f}, {24.0f, 24.0f} };
}
