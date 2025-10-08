#include "SceneManager.h"

#include "../Scenes/Scene.h"
#include "../Scenes/TestScene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (Scene* scene : Scenes)
	{
		delete scene;
		scene = nullptr;
	}
	Scenes.clear();
}

void SceneManager::Initialize()
{
	Scenes.push_back(new TestScene());
	LoadScene(L"Test Map");
}

void SceneManager::Tick(float DeltaTime)
{
	if (!CurrentScene)
		return;

	CurrentScene->Tick(DeltaTime);
}

void SceneManager::Render(Gdiplus::Graphics* InGraphics)
{
	if (!CurrentScene)
		return;
	CurrentScene->Render(InGraphics);
}

void SceneManager::LoadScene(const std::wstring& SceneName)
{
	Scene* NewScene = nullptr;
	for (Scene* scene : Scenes)
	{
		if (scene->GetName() == SceneName)
		{
			NewScene = scene;
			break;
		}
	}

	if (!NewScene)
		return;

	if (CurrentScene)
		CurrentScene->OnExit();
	
	CurrentScene = NewScene;
	CurrentScene->OnEnter();
}

