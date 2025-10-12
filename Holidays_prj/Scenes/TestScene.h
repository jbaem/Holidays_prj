#pragma once

#include "Scene.h"
#include "../Managers/EnemySpawner.h"

class TestScene : public Scene
{
public:
	TestScene();
	virtual void OnEnter() override;
	virtual void OnTick(float DeltaTime) override;


private:
	EnemySpawner* Spawner = nullptr;
};

