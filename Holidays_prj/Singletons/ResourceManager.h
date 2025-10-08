#pragma once

#include "../Common.h"

#include "TSingleton.h"
#include <unordered_map>

// 이미지 저장하고 있다가 호출하기
class ResourceManager : public TSingleton<ResourceManager>
{
	friend class TSingleton<ResourceManager>;
public:
	virtual void Initialize();
	virtual void Destroy();

	Gdiplus::Bitmap* GetImage(EResourceID InID);

	Gdiplus::Bitmap* GetImage(EResourceID InID, Gdiplus::PointF& Position, Gdiplus::PointF& Size);
	
private:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;

	bool LoadResourceFromFile(EResourceID InID, const wchar_t* InPath);
	bool CreateCompositeBackground();

	std::unordered_map<EResourceID, Gdiplus::Bitmap*> Resources;
};

