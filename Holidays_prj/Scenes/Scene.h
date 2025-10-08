#pragma once

#include "../Common.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "../Actors/AActor.h"
#include "../Actors/Background.h"

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void OnInitialize();
	virtual void OnDestroy();
	virtual void OnTick(float DeltaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);

	const std::wstring& GetName() const { return Name; }

protected:
	std::wstring Name = L"";
	std::unordered_map<ERenderLayer, std::vector<AActor*>> Actors;
};

