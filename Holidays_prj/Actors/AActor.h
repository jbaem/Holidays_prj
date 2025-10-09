#pragma once

#include "../Common.h"

#include <vector>
#include "../Components/Component.h"
#include <unordered_map>
#include <typeinfo>

class Scene;

class AActor
{
public:
	AActor() = delete;
	AActor(EResourceID InID);
	virtual ~AActor();

	virtual void OnInitialize() {}
	virtual void OnTick(float DeltaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);
	virtual void OnOverlap(AActor* Other) {};

	virtual void Destroy();
	inline bool IsPendingDestroy() const { return bIsPendingDestroy; }
	
	void AddComponent(Component* InComponent);
	void RemoveComponent(Component* InComponent);

	template<typename T>
	T* GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		for (const auto& pair : Components)
		{
			Component* Comp = pair.second;
			T* CastedComponents = dynamic_cast<T*>(Comp);
			if (CastedComponents)
				return CastedComponents;
		}
		return nullptr;
	}

	template<typename T>
	bool HasComponent() const { return GetComponent<T>() != nullptr; }

	// Getter
	inline const Gdiplus::PointF& GetPosition() const { return Position; }
	inline const Gdiplus::PointF& GetSize() const { return Size; }
	inline const Gdiplus::PointF& GetPivot() const { return Pivot; }
	inline const ERenderLayer GetLayer() const { return Layer;}
	Gdiplus::PointF GetRenderPosition() const;

	// Setter
	inline void SetPosition(const Gdiplus::PointF& InPosition) { Position = InPosition; }
	inline void SetPosition(float x, float y) { Position = { x, y }; }
	inline void SetSize(float Width, float Height) { Size = { Width, Height }; }
	inline void SetPivot(float x, float y) { Pivot = { x, y }; }
	inline void SetLayer(ERenderLayer InLayer) { Layer = InLayer; }
	inline void SetOwnerScene(Scene* InScene) { OwnerScene = InScene; }

protected:
	Gdiplus::PointF Position = { 0.0f, 0.0f };
	Gdiplus::PointF Size = { 64.0f, 64.0f };
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };

	float Angle = 0.0f;

	Gdiplus::Bitmap* Image = nullptr;
	ERenderLayer Layer = ERenderLayer::Misc;

	std::unordered_map<EComponentType, Component*> Components;

	bool bIsPendingDestroy = false;
	Scene* OwnerScene = nullptr;
};

