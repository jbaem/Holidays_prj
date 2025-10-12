#pragma once

#include "TSingleton.h"

#include "../Enums.h"
#include "../Common.h"

#include "../Scenes/Scene.h"

class SceneManager : public TSingleton<SceneManager>
{
	friend class TSingleton<SceneManager>;
public:
	virtual void Initialize();
	virtual void Destroy();

	void Tick(float DeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);

	void LoadScene(ESceneType InType);
	void RegisterActor(AActor* InActor);

	Scene* GetCurrentScene() const { return CurrentScene; }

private:
	SceneManager() = default;
	virtual ~SceneManager() = default;

	Scene* CurrentScene = nullptr;
};

