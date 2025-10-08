#include "AActor.h"

#include "../Singletons/GameManager.h"
#include "../Singletons/ResourceManager.h"

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

void AActor::DestroyActor()
{
	if (!IsPendingDesytoy)
	{
		IsPendingDesytoy = true;
		GameManager::GetInstance().RequestDestroy(this);
	}
}
void AActor::OnDestroy()
{
	while (!Components.empty())
	{
		RemoveComponent(Components[0]);
	}
	Components.clear();
}

void AActor::OnTick(float DeltaTime)
{
	for (auto& component : Components)
	{
		component->OnTick(DeltaTime);
	}
}

void AActor::OnRender(Gdiplus::Graphics* InGraphics)
{
	if (!InGraphics || !Image)
		return;

	// 현재 변환 상태
	Gdiplus::Matrix oldTransform;
	InGraphics->GetTransform(&oldTransform);
	// 회전 중심점-> 객체의 중심
	InGraphics->TranslateTransform(Position.X, Position.Y);
	// 회전
	InGraphics->RotateTransform(Angle);
	InGraphics->TranslateTransform(-Position.X, -Position.Y);

	InGraphics->SetTransform(&oldTransform);
}


void AActor::AddComponent(Component* InComponent)
{
	if (!InComponent)
		return;
	Components.push_back(InComponent);
}

void AActor::RemoveComponent(Component* InComponent)
{
	if (!InComponent)
		return;

	auto iter = std::find(Components.begin(), Components.end(), InComponent);
	if (iter == Components.end())
		return;

	(*iter)->OnDestroy();
	std::swap(*iter, Components.back());
	Components.pop_back();
	delete InComponent;
	InComponent = nullptr;
}
