#include "SceneManager.h"

#include "../Scenes/Scene.h"
#include "../Scenes/TestScene.h"

void SceneManager::Initialize()
{
	CurrentScene = nullptr;
	LoadScene(ESceneType::PlayerTest);
}

void SceneManager::Destroy()
{
	delete CurrentScene;
	CurrentScene = nullptr;
}

void SceneManager::Tick(float DeltaTime)
{
	if (!CurrentScene)
		return;
	CurrentScene->OnTick(DeltaTime);
}

void SceneManager::Render(Gdiplus::Graphics* InGraphics)
{
	if (!CurrentScene)
		return;
	CurrentScene->OnRender(InGraphics);
}

void SceneManager::LoadScene(ESceneType InType)
{
	Scene* NewScene = nullptr;
	switch (InType)
	{
	case ESceneType::PlayerTest:
		NewScene = new TestScene();
		break;
	}
	if (!NewScene)
		return;

	if (CurrentScene)
		CurrentScene->OnDestroy();
	
	CurrentScene = NewScene;
	CurrentScene->OnInitialize();
}

