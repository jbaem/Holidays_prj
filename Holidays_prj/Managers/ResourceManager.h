#pragma once

#include "../Common.h"

#include "TSingleton.h"
#include <unordered_map>

class ResourceManager : public TSingleton<ResourceManager>
{
	friend class TSingleton<ResourceManager>;
public:
	virtual void Initialize();
	virtual void Destroy();

	Gdiplus::Bitmap* GetImage(EResourceID InID);
	Gdiplus::Bitmap* GetImage(EPlayerState InState);
	

private:
	virtual ~ResourceManager() = default;

	void LoadResources();
	void LoadPlayerResources();

	bool LoadResourceFromFile(EResourceID InID, const wchar_t* InPath);
	bool LoadResourceFromFile(EPlayerState InState, const wchar_t* InPath);
	
	bool CreateCompositeBackground();
	void CropTileset();
	void CropEffects();

	std::unordered_map<EResourceID, Gdiplus::Bitmap*> Resources;
	std::unordered_map<EPlayerState, Gdiplus::Bitmap*> PlayerResources;
};

