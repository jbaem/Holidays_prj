#pragma once

#include "TSingleton.h"

#include "../Common.h"

class UIManager : public TSingleton<UIManager>
{
	friend class TSingleton<UIManager>;
public:
	virtual void Initialize() override;
	virtual void Destroy() override;

	void Tick(float DeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);

	void AddEnemyKillCount();

private:
	UIManager() = default;
	virtual ~UIManager() = default;

	void ShowPlayerHealth(Gdiplus::Graphics* InGraphics);
	void ShowPlayTime(Gdiplus::Graphics* InGraphics);
	void ShowEnemyKillCount(Gdiplus::Graphics* InGraphics);

	float PlayTime = 0.0f;
	int EnemyKillCount = 0;

	Gdiplus::SolidBrush* BarBrush = nullptr;
	Gdiplus::SolidBrush* HpBrush = nullptr;
	Gdiplus::SolidBrush* TextBrush = nullptr;
	Gdiplus::Font* UIFont = nullptr;
};

