#pragma once

#include "../Common.h"

#include <vector>
#include "../Components/Component.h"
#include <unordered_map>

class AActor
{
public:
	AActor() = delete;
	AActor(EResourceID InID);
	virtual ~AActor() = default;

	virtual void OnInitialize() {}
	virtual void OnDestroy();
	virtual void OnTick(float DeltaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);

	virtual void DestroyActor();
	virtual void OnOverlap(AActor* Other) {};
	
	void AddComponent(Component* InComponent);
	void RemoveComponent(Component* InComponent);

	template<typename T>
	T* GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		for (auto Comp : Components)
		{
			T* CastedComponent = dynamic_cast<T*>(Comp);
			if (CastedComponent)
				return CastedComponent;
		}
		return nullptr;
	}

	template<typename T>
	bool HasComponent() const { return GetComponent<T>() != nullptr; }

	// Getter
	inline Gdiplus::PointF& GetPosition() { return Position; }
	inline Gdiplus::PointF GetSize() const { return Size; }
	inline const Gdiplus::PointF& GetPivot() const { return Pivot; }
	inline const ERenderLayer GetLayer() const { return Layer;}

	// Setter
	inline void SetPosition(float x, float y) { Position.X = x; Position.Y = y; }
	inline void SetSize(int Width, int Height) { Size.X = Width; Size.Y = Height; }
	inline void SetPivot(int x, int y) { Pivot.X = x; Pivot.Y = y; }
	inline void SetLayer(ERenderLayer InLayer) { Layer = InLayer; }

protected:
	Gdiplus::PointF Position = { 0.0f, 0.0f };
	Gdiplus::PointF Pivot = { 0.0f, 0.0f };

	float Angle = 0.0f;
	Gdiplus::PointF Size = { 64.0f, 64.0f };

	Gdiplus::Bitmap* Image = nullptr;

	ERenderLayer Layer = ERenderLayer::Misc;

	std::vector<Component*> Components;

private:
	bool IsPendingDesytoy = false;
};

