#include "EnemySpawner.h"
#include "../Actors/APlayer.h"
#include "../Actors/AEnemy.h"
#include "../Managers/GameManager.h"
#include "../Managers/Factory.h"

#include <random>


void EnemySpawner::OnTick(float DeltaTime)
{
	TimeSinceLastSpawn += DeltaTime;
    if(TimeSinceLastSpawn >= SpawnInterval)
    {
        SpawnEnemy();
        TimeSinceLastSpawn = 0.0f;
        
        if(++TotalSpawnCount % 5 == 0 && SpawnInterval > 1.0f)
        {
            SpawnInterval *= 0.9f;
		}
	}
}


void EnemySpawner::SpawnEnemy()
{
    APlayer* player = GameManager::GetInstance().GetMainPlayer();
    if (!player) return;

    Gdiplus::PointF PlayerPos = player->GetPosition();

	int RandomNumber = rand() % 2;
    
    Gdiplus::PointF SpawnPos;
    if(RandomNumber == 0)
    {
        SpawnPos = { 100.0f, 100.0f };
    }
    else
    {
        SpawnPos = { GameManager::ScreenWidth - 100.0f, 100.0f };
    }

    AEnemy* enemy = Factory::GetInstance().SpawnActor<AEnemy>(EResourceID::Golem, ERenderLayer::Enemy);
    if (enemy)
    {
        enemy->SetPosition(SpawnPos);
    }
}