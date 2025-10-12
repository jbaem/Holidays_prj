#include "AActor.h"

#include "../Managers/GameManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/SceneManager.h"
#include <typeinfo>

AActor::AActor(EResourceID InID)
{
	Image = ResourceManager::GetInstance().GetImage(InID);
	if (!Image)
		return;

	Size = {
		static_cast<float>(Image->GetWidth()),
		static_cast<float>(Image->GetHeight())
	};
}

AActor::~AActor()
{
	for (auto const& [key, val] : Components)
	{
		delete val;
	}
	Components.clear();
}

void AActor::OnInitialize()
{
	OwnerScene = SceneManager::GetInstance().GetCurrentScene();
	if(OwnerScene)
		OwnerScene->RegisterActor(this);
}

void AActor::OnTick(float DeltaTime)
{
	for (auto const& [key, val] : Components)
	{
		val->OnTick(DeltaTime);
	}
}

void AActor::OnRender(Gdiplus::Graphics* InGraphics)
{
	if (!InGraphics)
		return;

	for (auto const& [key, val] : Components)
	{
		val->OnRender(InGraphics);
	}
}

void AActor::Destroy()
{
	if (!bIsPendingDestroy)
	{
		bIsPendingDestroy = true;
		OwnerScene->RequestDestroy(this);
	}
}

void AActor::AddComponent(Component* InComponent)
{
	if (!InComponent)
		return;

	EComponentType TempType = InComponent->GetType();
	if (Components.find(TempType) != Components.end())
	{
		delete Components[TempType];
	}
	Components[TempType] = InComponent;
	InComponent->SetOwner(this);
}

void AActor::RemoveComponent(Component* InComponent)
{
	if (!InComponent)
		return;

	EComponentType TempType = InComponent->GetType();
	if (Components.find(TempType) == Components.end())
		return;

	delete Components[TempType];
	Components[TempType] = nullptr;
	Components.erase(TempType);
}

Gdiplus::PointF AActor::GetRenderPosition() const
{
	return {
		Position.X - Size.X * Pivot.X,
		Position.Y - Size.Y * Pivot.Y
	};
}
