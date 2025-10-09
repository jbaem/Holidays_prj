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

Gdiplus::Bitmap* ResourceManager::GetImage(EResourceID InID, Gdiplus::PointF& Position, Gdiplus::PointF& Size)
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

	delete LoadedImage;
	LoadedImage = nullptr;

	OutputDebugString(L"이미지 로드 실패");
	MessageBox (
		GameManager::GetInstance().GetWindowHandle(),
		L"이미지 로드 실패",
		L"오류",
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
		OutputDebugString(L"배경 이미지 결합 실패");
		return false;
	}

	UINT Width = bg1->GetWidth();
	UINT Height = bg1->GetHeight();
	Gdiplus::Bitmap* CompositeImage = new Gdiplus::Bitmap(Width, Height, PixelFormat32bppARGB);
	Gdiplus::Graphics* GraphicsTool = Gdiplus::Graphics::FromImage(CompositeImage);

	GraphicsTool->DrawImage(bg1, 0, 0, Width, Height);
	GraphicsTool->DrawImage(bg2, 0, 0, Width, Height);
	GraphicsTool->DrawImage(bg3, 0, 0, Width, Height);

	Resources[EResourceID::BackGround] = CompositeImage;

	delete GraphicsTool;
	return true;
}
