#pragma once

class EnemySpawner
{
public:
	EnemySpawner()
		:SpawnInterval(5.0f), TimeSinceLastSpawn(0.0f) 
	{ 
	}
	virtual ~EnemySpawner() = default;

	virtual void OnTick(float DeltaTime);

	void SpawnEnemy();

private:
	float SpawnInterval = 5.0f;
	float TimeSinceLastSpawn = 0.0f;
	int TotalSpawnCount = 0;
	int LevelUpCount = 3;
};

