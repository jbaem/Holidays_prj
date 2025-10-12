#pragma once

#include "AActor.h"

class ATerrain : public AActor
{
public:
	ATerrain() = delete;
	ATerrain(EResourceID InID, EBlockType InType);
	virtual ~ATerrain() = default;

	virtual void OnInitialize() override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

	// Getter
	inline EBlockType GetTerrainType() const { return Type; }
	
	// Setter
	inline void SetTerrainType(EBlockType InType) { Type = InType; }
	inline void SetResourceType(EResourceID InType) { ResourceType = InType; }
	inline void SetSpriteSize(const Gdiplus::PointF& InSize) { SpriteSize = InSize; }
	inline void SetOffset(const Gdiplus::PointF& InOffset) { ImageOffset = InOffset; }

private:
	Gdiplus::PointF ImageOffset = { 0.0f, 0.0f };
	float ImageScale = 2.0f;
	Gdiplus::PointF SpriteSize = { 0.0f, 0.0f };
	EResourceID ResourceType = EResourceID::None;
	EBlockType Type = EBlockType::None;
};

