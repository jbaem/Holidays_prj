#pragma once

#include "../Enums.h"
#include <gdiplus.h>

class AActor;

class Component
{
public:
	Component(EComponentType InType)
		: Type(InType) {};
	virtual ~Component() = default;

	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void OnTick(float DeltaTime) {};
	virtual void OnRender(Gdiplus::Graphics* InGraphics) {};

	// Getter
	inline AActor* GetOwner() { return Owner; }
	inline EComponentType GetType() { return Type; }

	// Setter
	inline void SetOwner(AActor* InOwner) { Owner = InOwner; }

protected:
	AActor* Owner = nullptr;
	EComponentType Type;
};