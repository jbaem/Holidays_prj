#include "TestScene.h"
#include "../Actors/APlayer.h"
#include "../Actors/ATerrain.h"

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

	const float WallThickness = 50.0f;
	const float PlatformWidth = 200.0f;
	const float PlatformHeight = 30.0f;

    // --- 천장 (Top Wall) 생성 ---
    ATerrain* TopWall = new ATerrain(EResourceID::None, ETerrainType::Solid);
    //ATerrain* TopWall = new ATerrain(ETerrainType::Solid);
    TopWall->SetSize(GameManager::ScreenWidth, WallThickness);
    TopWall->SetPosition(GameManager::ScreenWidth / 2.0f, WallThickness / 2.0f);
    TopWall->OnInitialize();
    RegisterActor(TopWall);

    // --- 바닥 (Bottom Wall) 생성 ---
    ATerrain* BottomWall = new ATerrain(EResourceID::None, ETerrainType::Solid);
    //ATerrain* BottomWall = new ATerrain(ETerrainType::Solid);
    BottomWall->SetSize(GameManager::ScreenWidth, WallThickness);
    BottomWall->SetPosition(GameManager::ScreenWidth / 2.0f, GameManager::ScreenHeight - WallThickness / 2.0f);
	BottomWall->OnInitialize();
    RegisterActor(BottomWall);

    // --- 왼쪽 벽 (Left Wall) 생성 ---
    ATerrain* LeftWall = new ATerrain(EResourceID::None, ETerrainType::Solid);
    //ATerrain* LeftWall = new ATerrain(ETerrainType::Solid);
    LeftWall->SetSize(WallThickness, GameManager::ScreenHeight);
    LeftWall->SetPosition(WallThickness / 2.0f, GameManager::ScreenHeight / 2.0f);
	LeftWall->OnInitialize();
    RegisterActor(LeftWall);

    // --- 오른쪽 벽 (Right Wall) 생성 ---
    ATerrain* RightWall = new ATerrain(EResourceID::None, ETerrainType::Solid);
    //ATerrain* RightWall = new ATerrain(ETerrainType::Solid);
    RightWall->SetSize(WallThickness, GameManager::ScreenHeight);
    RightWall->SetPosition(GameManager::ScreenWidth - WallThickness / 2.0f, GameManager::ScreenHeight / 2.0f);
	RightWall->OnInitialize();
    RegisterActor(RightWall);

    // 1. 왼쪽 하단 플랫폼
    ATerrain* OneWayPlatform1 = new ATerrain(EResourceID::None, ETerrainType::OneWay);
    OneWayPlatform1->SetSize(PlatformWidth, PlatformHeight);
    OneWayPlatform1->SetPosition(GameManager::ScreenWidth / 4.0f, GameManager::ScreenHeight - WallThickness - 100.0f);
    RegisterActor(OneWayPlatform1);

    // 2. 중앙 중간 플랫폼
    ATerrain* OneWayPlatform2 = new ATerrain(EResourceID::None, ETerrainType::OneWay);
    OneWayPlatform2->SetSize(PlatformWidth + 50.0f, PlatformHeight);
    OneWayPlatform2->SetPosition(GameManager::ScreenWidth / 2.0f, GameManager::ScreenHeight - WallThickness - 250.0f);
    RegisterActor(OneWayPlatform2);

    // 3. 오른쪽 상단 플랫폼
    ATerrain* OneWayPlatform3 = new ATerrain(EResourceID::None, ETerrainType::OneWay);
    OneWayPlatform3->SetSize(PlatformWidth, PlatformHeight);
    OneWayPlatform3->SetPosition(GameManager::ScreenWidth * 3.0f / 4.0f, GameManager::ScreenHeight - WallThickness - 400.0f);
    RegisterActor(OneWayPlatform3);

    // 4. 좀 더 긴 중앙 플랫폼
    ATerrain* OneWayPlatform4 = new ATerrain(EResourceID::None, ETerrainType::OneWay);
    OneWayPlatform4->SetSize(PlatformWidth * 1.5f, PlatformHeight);
    OneWayPlatform4->SetPosition(GameManager::ScreenWidth / 2.0f, GameManager::ScreenHeight - WallThickness - 550.0f);
    RegisterActor(OneWayPlatform4);

}
