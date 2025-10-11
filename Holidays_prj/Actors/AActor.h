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

	// Lifecycle
	virtual void OnInitialize() {}
	virtual void OnTick(float DeltaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);
	virtual void OnOverlap(AActor* Other) {};

	virtual void Destroy();
	inline bool IsPendingDestroy() const { return bIsPendingDestroy; }
	
	// Component Management
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

	// Getter & Setter
	inline const Gdiplus::PointF& GetPosition() const { return Position; }
	inline void SetPosition(const Gdiplus::PointF& InPosition) { Position = InPosition; }
	inline void SetPosition(float x, float y) { Position = { x, y }; }
	Gdiplus::PointF GetRenderPosition() const;

	inline const Gdiplus::PointF& GetSize() const { return Size; }
	inline void SetSize(float Width, float Height) { Size = { Width, Height }; }
	inline void SetSize(const Gdiplus::PointF& InSize) { Size = InSize; }

	inline const Gdiplus::PointF& GetPivot() const { return Pivot; }
	inline void SetPivot(float x, float y) { Pivot = { x, y }; }
	inline void SetPivot(const Gdiplus::PointF& InPivot) { Pivot = InPivot; }

	inline const ERenderLayer GetLayer() const { return Layer; }
	inline void SetLayer(ERenderLayer InLayer) { Layer = InLayer; }

	inline const ELook GetLook() const { return Look; }
	inline void SetLook(ELook InLook) { Look = InLook; }

	inline void SetOwnerScene(Scene* InScene) { OwnerScene = InScene; }

protected:

	Gdiplus::PointF Position = { 0.0f, 0.0f };
	Gdiplus::PointF Size = { 64.0f, 64.0f };
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };

	ELook Look = ELook::Right;
	Gdiplus::Bitmap* Image = nullptr;
	ERenderLayer Layer = ERenderLayer::Misc;

	std::unordered_map<EComponentType, Component*> Components;

	bool bIsPendingDestroy = false;
	Scene* OwnerScene = nullptr;
};

