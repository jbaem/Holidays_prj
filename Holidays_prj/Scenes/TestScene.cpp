#include "TestScene.h"
#include "../Actors/APlayer.h"
#include "../Singletons/Factory.h"

TestScene::TestScene()
{
	Name = L"Test Map";
}

void TestScene::OnEnter()
{
	APlayer* Player = new APlayer(EResourceID::PlayerIdle);
	//APlayer* Player = Factory::GetInstance().SpawnActor(EResourceID::PlayerIdle, ERenderLayer::Player);
	Player->SetPosition(400, 300);
	Actors[ERenderLayer::Player].push_back(Player);
	


}
