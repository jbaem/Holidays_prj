#include "TestScene.h"

#include "../Managers/ResourceManager.h"

#include "../Actors/APlayer.h"
#include "../Actors/ATerrain.h"
#include "../Actors/ABullet.h"

#include "../Components/Physics.h"

#include "../Managers/Factory.h"

#include "../Actors/ABackground.h"

TestScene::TestScene()
{
	Name = L"Test Map";
}

void TestScene::OnEnter()
{
	Scene::OnEnter();
	MainPlayer->SetPosition(GameManager::ScreenWidth * 0.5f, 450.f);
	//MainPlayer->GetComponent<Physics>()->SetEnableGravity(false);

	ABackground* background = Factory::GetInstance().SpawnActor<ABackground>(EResourceID::BackGround, ERenderLayer::BackGround);
	RegisterActor(background);

	const float WallThickness = 24.0f;
	const float PlatformWidth = 400.0f;
	const float PlatformHeight = 48.0f;

    // Top Wall
    ATerrain* TopWall = new ATerrain(EResourceID::Wall, EBlockType::Solid);
    TopWall->SetSize(GameManager::ScreenWidth, WallThickness);
    TopWall->SetPosition(GameManager::ScreenWidth / 2.0f, WallThickness / 2.0f);
    TopWall->OnInitialize();
    RegisterActor(TopWall);

    // Left Wall
    ATerrain* LeftWall = new ATerrain(EResourceID::Wall, EBlockType::Solid);
    LeftWall->SetSize(WallThickness, GameManager::ScreenHeight);
    LeftWall->SetPosition(WallThickness / 2.0f, GameManager::ScreenHeight / 2.0f);
	LeftWall->OnInitialize();
    RegisterActor(LeftWall);

    // Right Wall
    ATerrain* RightWall = new ATerrain(EResourceID::Wall, EBlockType::Solid);
    RightWall->SetSize(WallThickness, GameManager::ScreenHeight);
    RightWall->SetPosition(GameManager::ScreenWidth - WallThickness / 2.0f, GameManager::ScreenHeight / 2.0f);
	RightWall->OnInitialize();
    RegisterActor(RightWall);

    // Bottom Wall
    ATerrain* BottomWall = new ATerrain(EResourceID::Platform, EBlockType::Solid);
    BottomWall->SetSize(GameManager::ScreenWidth, WallThickness);
    BottomWall->SetPosition(GameManager::ScreenWidth / 2.0f, GameManager::ScreenHeight - WallThickness / 2.0f);
    BottomWall->OnInitialize();
    RegisterActor(BottomWall);

	// Platforms1
    ATerrain* OneWayPlatform1 = new ATerrain(EResourceID::Platform, EBlockType::OneWay);
    OneWayPlatform1->SetSize(PlatformWidth, PlatformHeight);
    OneWayPlatform1->SetPosition(GameManager::ScreenWidth / 4.0f, GameManager::ScreenHeight - WallThickness - 100.0f);
    OneWayPlatform1->OnInitialize();
    RegisterActor(OneWayPlatform1);
    

	// Platforms2
    ATerrain* OneWayPlatform2 = new ATerrain(EResourceID::Platform, EBlockType::OneWay);
	OneWayPlatform2->SetSize(PlatformWidth + 50.0f, PlatformHeight);
    OneWayPlatform2->SetPosition(GameManager::ScreenWidth / 2.0f, GameManager::ScreenHeight - WallThickness - 250.0f);
    OneWayPlatform2->OnInitialize();
    RegisterActor(OneWayPlatform2);

	// Platforms3
    ATerrain* OneWayPlatform3 = new ATerrain(EResourceID::Platform, EBlockType::OneWay);
    OneWayPlatform3->SetSize(PlatformWidth, PlatformHeight);
    OneWayPlatform3->SetPosition(GameManager::ScreenWidth * 3.0f / 4.0f, GameManager::ScreenHeight - WallThickness - 400.0f);
    OneWayPlatform3->OnInitialize();
    RegisterActor(OneWayPlatform3);

	// Platforms4
    ATerrain* OneWayPlatform4 = new ATerrain(EResourceID::Platform, EBlockType::OneWay);
    OneWayPlatform4->SetSize(PlatformWidth/4, PlatformHeight);
    OneWayPlatform4->SetPosition(GameManager::ScreenWidth / 2.0f, GameManager::ScreenHeight - WallThickness - 550.0f);
    OneWayPlatform4->OnInitialize();
    RegisterActor(OneWayPlatform4);

    auto* bulletR = Factory::GetInstance().SpawnActor<ABullet>(EResourceID::PlayerBullet, ERenderLayer::Bullet);
    auto* bulletL = Factory::GetInstance().SpawnActor<ABullet>(EResourceID::PlayerBullet, ERenderLayer::Bullet);
    auto* bulletU = Factory::GetInstance().SpawnActor<ABullet>(EResourceID::PlayerBullet, ERenderLayer::Bullet);
    auto* bulletD = Factory::GetInstance().SpawnActor<ABullet>(EResourceID::PlayerBullet, ERenderLayer::Bullet);

    bulletR->SetPosition(GameManager::ScreenWidth/2, GameManager::ScreenHeight/2);
    bulletL->SetPosition(GameManager::ScreenWidth/2, GameManager::ScreenHeight/2);
    bulletU->SetPosition(GameManager::ScreenWidth/2, GameManager::ScreenHeight/2);
    bulletD->SetPosition(GameManager::ScreenWidth/2, GameManager::ScreenHeight/2);

}
