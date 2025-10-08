#include "TestScene.h"
#include "../Actors/APlayer.h"
#include "../Singletons/Factory.h"
#include "../Actors/ATerrain.h"
#include "../Singletons/Factory.h"

TestScene::TestScene()
{
	Name = L"Test Map";
}

void TestScene::OnInitialize()
{
	Background* background = Factory::GetInstance().SpawnActor<Background>(EResourceID::BackGround, ERenderLayer::BackGround);
	Actors[ERenderLayer::BackGround].push_back(background);

	ATerrain* Terrain = Factory::GetInstance().SpawnActor<ATerrain>(EResourceID::None, ERenderLayer::Terrain);
	Terrain->SetPosition(GameManager::ScreenWidth * 0.5f, 550.f);
	Actors[ERenderLayer::Terrain].push_back(Terrain);

	GameManager::GetInstance().SetMainPlayer();
	APlayer* Player = GameManager::GetInstance().GetMainPlayer();
	Player->SetPosition(GameManager::ScreenWidth * 0.5f, 450.f);
	Player->GetComponent<Physics>()->SetEnableGravity(false);
	Actors[ERenderLayer::Player].push_back(Player);
}
