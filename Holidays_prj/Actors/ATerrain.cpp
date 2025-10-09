#include "ATerrain.h"

#include "../Components/RectangleCollider.h"
#include "../Enums.h"
#include "../Managers/GameManager.h"

ATerrain::ATerrain(EResourceID InID, ETerrainType InType)
	:AActor(InID), Type(InType)
{
	SetSize(GameManager::ScreenWidth, 50);
	AddComponent(new RectangleCollider(EPhysicsLayer::Terrain,
		GetSize().X, GetSize().Y));
}

void ATerrain::OnInitialize()
{
	GetComponent<RectangleCollider>()->SetLayer(EPhysicsLayer::Terrain);
	GetComponent<RectangleCollider>()->SetSize(GetSize().X, GetSize().Y);
}

