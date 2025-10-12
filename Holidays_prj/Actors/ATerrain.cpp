#include "ATerrain.h"

#include "../Components/RectangleCollider.h"
#include "../Enums.h"
#include "../Managers/GameManager.h"

ATerrain::ATerrain(EResourceID InID, EBlockType InType)
	:AActor(InID), ResourceType(InID), Type(InType)
{
	SetSize(GameManager::ScreenWidth / 2, 48);
	AddComponent(new RectangleCollider(this, EPhysicsLayer::Terrain,
		GetSize().X, GetSize().Y));
	Layer = ERenderLayer::Terrain;
}

void ATerrain::OnInitialize()
{
	SpriteSize = { 24.0f, 24.0f };

	GetComponent<RectangleCollider>()->SetLayer(EPhysicsLayer::Terrain);
	GetComponent<RectangleCollider>()->SetSize(GetSize().X, GetSize().Y);
}

void ATerrain::OnRender(Gdiplus::Graphics* InGraphics)
{
	AActor::OnRender(InGraphics);

	if (!Image || SpriteSize.X < 0.1 || SpriteSize.Y < 0.1)
		return;
	
	float TileWidth = SpriteSize.X * ImageScale;
	float TileHeight = SpriteSize.Y * ImageScale;

	for(int i = 0; i < GetSize().X; i += TileWidth)
	{
		for(int j = 0; j < GetSize().Y; j += TileHeight)
		{
			float remainX = TileWidth  < GetSize().X - i ? TileWidth  : GetSize().X - i;
			float remainY = TileHeight < GetSize().Y - j ? TileHeight : GetSize().Y - j;

			Gdiplus::RectF DestRect = {
				GetRenderPosition().X + i,
				GetRenderPosition().Y + j,
				remainX,
				remainY
			};

			InGraphics->DrawImage(
				Image,
				DestRect,
				0, 0, remainX / ImageScale, remainY / ImageScale,
				Gdiplus::UnitPixel
			);
		}
	}
}



