#pragma once

#include "TSingleton.h"
#include "../Enums.h"
#include <vector>

// 面倒 贸府 包府
class CollisionManager : public TSingleton<CollisionManager>
{
	friend class TSingleton<CollisionManager>;
public:
	void Initialize();
	void Destroy();
	bool ShouldCollision(EPhysicsLayer a, EPhysicsLayer b);

private:
	void SetCollisionRule(EPhysicsLayer a, EPhysicsLayer b);
	std::vector<uint32_t> CollisionMatrix;
};

