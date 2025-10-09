#include "ResourceManager.h"

#include "GameManager.h"

void ResourceManager::Initialize()
{
	Resources[EResourceID::None] = nullptr;
	LoadResourceFromFile(EResourceID::BackGround1, L"./Images/Tile/BG1.png");
	LoadResourceFromFile(EResourceID::BackGround2, L"./Images/Tile/BG2.png");
	LoadResourceFromFile(EResourceID::BackGround3, L"./Images/Tile/BG3.png");
	LoadResourceFromFile(EResourceID::PlayerIdle, L"./Images/Player/_Idle.png");
	LoadResourceFromFile(EResourceID::PlayerMove, L"./Images/Player/_Run.png");
	

	CreateCompositeBackground();
}

void ResourceManager::Destroy()
{
	for (auto& Resource : Resources)
	{
		delete Resource.second;
		Resource.second = nullptr;
	}
	Resources.clear();
}

Gdiplus::Bitmap* ResourceManager::GetImage(EResourceID InID)
{
	if (Resources.find(InID) == Resources.end())
		return nullptr;

	return Resources[InID];
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

	OutputDebugString(L"Fail to Load Image\n");
	MessageBox (
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
