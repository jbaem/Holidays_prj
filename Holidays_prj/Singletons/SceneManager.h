#pragma once

#include "../Common.h"

#include "TSingleton.h"
#include "../Scenes/Scene.h"

class SceneManager : public TSingleton<SceneManager>
{
	friend class TSingleton<SceneManager>;
public:
	void Initialize();
	void Tick(float DeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);

	void LoadScene(const std::wstring& SceneName);

private:
	SceneManager();
	~SceneManager();

	Scene* CurrentScene = nullptr;
	std::vector<Scene*> Scenes;
};

