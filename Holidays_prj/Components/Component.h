#pragma once

#include "../Enums.h"

class AActor;

class Component
{
public:
	Component(AActor* InOwner, EComponentType InType)
		: Owner(InOwner), Type(InType) {};
	virtual ~Component() = default;

	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void OnTick(float DeltaTime) {};

	// Getter
	inline AActor* GetOwner() { return Owner; }
	inline EComponentType GetType() { return Type; }

protected:
	AActor* Owner = nullptr;
	EComponentType Type;
};