#pragma once

#include "TSingleton.h"
#include "../Enums.h"
#include <vector>

class CollisionManager : public TSingleton<CollisionManager>
{
	friend class TSingleton<CollisionManager>;
public:
	virtual void Initialize();
	virtual void Destroy();

	bool ShouldCollision(EPhysicsLayer a, EPhysicsLayer b);
private:
	virtual ~CollisionManager() = default;
	
	void SetCollisionRule(EPhysicsLayer a, EPhysicsLayer b);
	std::vector<uint32_t> CollisionMatrix;
};

