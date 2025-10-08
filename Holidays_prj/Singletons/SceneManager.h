#pragma once

#include "../Common.h"

#include "TSingleton.h"
#include "../Scenes/Scene.h"

// ¾À °ü¸®
class SceneManager : public TSingleton<SceneManager>
{
	friend class TSingleton<SceneManager>;
public:
	void Initialize();
	void Destroy();
	void Tick(float DeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);

	void LoadScene(ESceneType InType);

private:
	SceneManager() = default;
	virtual ~SceneManager() = default;

	Scene* CurrentScene = nullptr;
};

