#include "AActor.h"

#include "../Singletons/GameManager.h"
#include "../Singletons/ResourceManager.h"
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
	if (Image)
	{
		InGraphics->DrawImage(
			Image,
			RenderPos.X, RenderPos.Y,
			Size.X, Size.Y
		);
	}
	else
	{
		Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
		InGraphics->FillEllipse(&RedBrush,
			RenderPos.X, RenderPos.Y,
			Size.X, Size.Y
		);
	}
}


void AActor::Destroy()
{
	if (!bIsPendingDestroy)
	{
		bIsPendingDestroy = true;
		GameManager::GetInstance().RequestDestroy(this);
	}
}

void AActor::AddComponent(Component* InComponent)
{
	if (InComponent)
	{
		Components[typeid(*InComponent).hash_code()] = InComponent;
	}
}

void AActor::RemoveComponent(Component* InComponent)
{
	if (InComponent)
	{
		auto FindIt = Components.find(typeid(*InComponent).hash_code());
		if (FindIt != Components.end())
		{
			delete FindIt->second;
			FindIt->second = nullptr;
		}
	}
}

Gdiplus::PointF AActor::GetRenderPosition() const
{
	return {
		Position.X - Size.X * Pivot.X,
		Position.Y - Size.Y * Pivot.Y
	};
}
