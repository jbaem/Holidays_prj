#pragma once

#include "../Common.h"
#include <vector>
#include <string>
#include <unordered_map>

class AActor;

class Scene
{
public:
	virtual ~Scene();

	virtual void OnEnter();
	virtual void OnExit();
	virtual void Tick(float DeltaTime);
	virtual void Render(Gdiplus::Graphics* InGraphics);

	const std::wstring& GetName() const { return Name; }
protected:
	std::wstring Name = L"";
	std::unordered_map<ERenderLayer, std::vector<AActor*>> Actors;
};

