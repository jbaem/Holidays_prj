#include "SceneHandler.h"

#include "../Scenes/Scene.h"
#include "../Scenes/TestScene.h"

SceneHandler::SceneHandler()
{
	LoadScene(ESceneType::PlayerTest);
}

SceneHandler::~SceneHandler()
{
	delete CurrentScene;
	CurrentScene = nullptr;
}

void SceneHandler::Tick(float DeltaTime)
{
	if (!CurrentScene)
		return;
	CurrentScene->OnTick(DeltaTime);
}

void SceneHandler::Render(Gdiplus::Graphics* InGraphics)
{
	if (!CurrentScene)
		return;
	CurrentScene->OnRender(InGraphics);
}

void SceneHandler::LoadScene(ESceneType InType)
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

