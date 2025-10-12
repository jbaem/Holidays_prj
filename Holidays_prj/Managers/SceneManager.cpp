#include "SceneManager.h"

#include "../Scenes/Scene.h"
#include "../Scenes/TestScene.h"
#include "UIManager.h"


void SceneManager::Initialize()
{
	LoadScene(ESceneType::PlayerTest);
}

void SceneManager::Destroy()
{
	if (CurrentScene)
		CurrentScene->OnExit();

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
		CurrentScene->OnExit();

	CurrentScene = NewScene;
	CurrentScene->OnEnter();
}

void SceneManager::RegisterActor(AActor* InActor)
{
	if (!InActor || !CurrentScene)
		return;
	CurrentScene->RegisterActor(InActor);
}