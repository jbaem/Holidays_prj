#pragma once

#include "AActor.h"

class ATerrain : public AActor
{
public:
	ATerrain() = delete;
	ATerrain(EResourceID InID, ETerrainType InType);
	virtual ~ATerrain() = default;

	virtual void OnInitialize() override;

	// Getter
	inline ETerrainType GetTerrainType() const { return Type; }
	
	// Setter
	inline void SetTerrainType(ETerrainType InType) { Type = InType; }
	inline void SetResourceType(EResourceID InType) { ResourceType = InType; }
	inline void SetSpritePosition(const Gdiplus::PointF& InPosition) { SpritePosition = InPosition; }
	inline void SetSpriteSize(const Gdiplus::PointF& InSize) { SpriteSize = InSize; }

private:
	Gdiplus::PointF SpritePosition = { 0.0f, 0.0f };
	Gdiplus::PointF SpriteSize = { 0.0f, 0.0f };
	EResourceID ResourceType = EResourceID::None;
	ETerrainType Type = ETerrainType::None;
};

