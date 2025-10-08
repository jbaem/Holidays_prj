#include "ResourceManager.h"

#include "GameManager.h"

void ResourceManager::Initialize()
{
	Resources[EResourceID::None] = nullptr;
	LoadResourceFromFile(EResourceID::Player, L"./Images/Player.png");
	LoadResourceFromFile(EResourceID::PlayerIdle, L"./Images/Player/_Idle.png");
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
