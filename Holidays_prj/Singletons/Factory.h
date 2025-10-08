#pragma once

#include "TSingleton.h"

#include "GameManager.h"
#include "../Actors/AActor.h"

class Factory : public TSingleton<Factory>
{
	friend class TSingleton<Factory>;
public:
	template<typename T>
	typename std::enable_if<std::is_base_of<AActor, T>::value, T*>::type 
	SpawnActor(EResourceID InID = EResourceID::None, ERenderLayer InLayer = ERenderLayer::Misc)
	{
		T* NewActor = new T(InID);
		NewActor->SetLayer(InLayer);
		NewActor->OnInitialize();
		GameManager::GetInstance().RegisterActor(InLayer, NewActor);
		return NewActor;
	}

private:
	Factory() = default;
	virtual ~Factory() = default;
};