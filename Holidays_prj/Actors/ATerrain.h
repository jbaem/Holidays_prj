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
	
private:
	ETerrainType Type = ETerrainType::None;
};

