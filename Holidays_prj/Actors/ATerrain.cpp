#include "ATerrain.h"

#include "../Components/RectangleCollider.h"
#include "../Enums.h"
#include "../Singletons/GameManager.h"

ATerrain::ATerrain(EResourceID InID)
	:AActor(InID)
{
	SetSize(GameManager::ScreenWidth, 50);
	AddComponent(new RectangleCollider(this, EPhysicsLayer::Terrain,
		GetSize().X, GetSize().Y));
}
