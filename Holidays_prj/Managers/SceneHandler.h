#pragma once

#include "../Common.h"

#include "TSingleton.h"
#include "../Scenes/Scene.h"

class SceneHandler
{
public:
	SceneHandler();
	~SceneHandler();

	void Tick(float DeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);

	void LoadScene(ESceneType InType);

private:
	Scene* CurrentScene = nullptr;
};

