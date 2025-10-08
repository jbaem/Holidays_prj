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

private:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;

	bool LoadResourceFromFile(EResourceID InID, const wchar_t* InPath);

	std::unordered_map<EResourceID, Gdiplus::Bitmap*> Resources;
};

