#pragma once

#include "TSingleton.h"

#include "../Actors/AActor.h"

class Factory : public TSingleton<Factory>
{
	friend class TSingleton<Factory>;
public:
	template<typename T>
	typename std::enable_if<std::is_base_of<AActor, T>::value, T*>::type 
	SpawnActor(ResourceID InID = ResourceID::None)
	{
		T* NewActor = new T(InID);
		// TODO: set layer, initialize, register
		return NewActor;
	}

private:
	Factory() = default;
	virtual ~Factory() = default;
};