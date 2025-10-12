#include "CollisionManager.h"
#include "../Scenes/Scene.h"
#include "GameManager.h"

void CollisionManager::Initialize()
{
	CollisionMatrix.resize(32, 0);

	// Player
	SetCollisionRule(EPhysicsLayer::Player, EPhysicsLayer::Enemy);
	SetCollisionRule(EPhysicsLayer::Player, EPhysicsLayer::EnemyBullet);
	SetCollisionRule(EPhysicsLayer::Player, EPhysicsLayer::Terrain);
	SetCollisionRule(EPhysicsLayer::Player, EPhysicsLayer::SolidTerrain);
	SetCollisionRule(EPhysicsLayer::Player, EPhysicsLayer::OneWayTerrain);

	// Enemy
	SetCollisionRule(EPhysicsLayer::Enemy, EPhysicsLayer::PlayerBullet);
	SetCollisionRule(EPhysicsLayer::Enemy, EPhysicsLayer::Terrain);
	SetCollisionRule(EPhysicsLayer::Enemy, EPhysicsLayer::SolidTerrain);
	SetCollisionRule(EPhysicsLayer::Enemy, EPhysicsLayer::OneWayTerrain);

	// PlayerBullet
	//SetCollisionRule(EPhysicsLayer::PlayerBullet, EPhysicsLayer::Terrain);
	//SetCollisionRule(EPhysicsLayer::PlayerBullet, EPhysicsLayer::SolidTerrain);

	// EnemyBullet
	//SetCollisionRule(EPhysicsLayer::EnemyBullet, EPhysicsLayer::Terrain);
	//SetCollisionRule(EPhysicsLayer::EnemyBullet, EPhysicsLayer::SolidTerrain);
}

void CollisionManager::Destroy()
{
	CollisionMatrix.clear();
}

bool CollisionManager::ShouldCollision(EPhysicsLayer a, EPhysicsLayer b)
{
	uint32_t IndexA = static_cast<uint32_t>(log2(static_cast<double>(a)));
	return (CollisionMatrix[IndexA] & static_cast<uint32_t>(b)) != 0;
}

void CollisionManager::SetCollisionRule(EPhysicsLayer a, EPhysicsLayer b)
{
	uint32_t IndexA = static_cast<uint32_t>(log2(static_cast<double>(a)));
	CollisionMatrix[IndexA] |= static_cast<uint32_t>(b);

	uint32_t IndexB = static_cast<uint32_t>(log2(static_cast<double>(b)));
	CollisionMatrix[IndexB] |= static_cast<uint32_t>(a);
}
