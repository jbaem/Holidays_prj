#include "AActor.h"

#include "../Managers/GameManager.h"
#include "../Managers/ResourceManager.h"
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

	Gdiplus::PointF RenderPos = GetRenderPosition();
	if(!Image)
	{
		Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
		InGraphics->FillEllipse(&RedBrush,
			RenderPos.X, RenderPos.Y,
			Size.X, Size.Y
		);
	}

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
