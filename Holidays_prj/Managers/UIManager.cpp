#include "UIManager.h"

#include "GameManager.h"


void UIManager::Initialize()
{
    BarBrush = new Gdiplus::SolidBrush(Gdiplus::Color(100, 100, 100));
    HpBrush = new Gdiplus::SolidBrush(Gdiplus::Color(200, 50, 50));
	TextBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255));
	UIFont = new Gdiplus::Font(L"Arial", 18);
}

void UIManager::Destroy()
{
	delete UIFont;
	UIFont = nullptr;
    delete TextBrush;
	TextBrush = nullptr;
    delete HpBrush;
	HpBrush = nullptr;
    delete BarBrush;
    BarBrush = nullptr;
}

void UIManager::Tick(float DeltaTime)
{
	PlayTime += DeltaTime;
}

void UIManager::Render(Gdiplus::Graphics* InGraphics)
{
    ShowPlayerHealth(InGraphics);
    ShowPlayTime(InGraphics);
	ShowEnemyKillCount(InGraphics);
}

void UIManager::AddEnemyKillCount()
{
    ++EnemyKillCount;
}

void UIManager::ShowPlayerHealth(Gdiplus::Graphics* InGraphics)
{
    APlayer* Player = GameManager::GetInstance().GetMainPlayer();
    if (Player)
    {
        float MaxHp = Player->GetMaxHealth();
        float CurrentHp = Player->GetHealth();
        float BarWidth = 200.0f;
        float BarHeight = 24.0f;
        float HpRatio = MaxHp > 0 ? CurrentHp / MaxHp : 0.0f;

        Gdiplus::RectF BarRect(20, 20, BarWidth, BarHeight);
        InGraphics->FillRectangle(BarBrush, BarRect);

        Gdiplus::RectF HpRect(20, 20, BarWidth * HpRatio, BarHeight);
        InGraphics->FillRectangle(HpBrush, HpRect);

        std::wstring HpText = std::to_wstring((int)CurrentHp) + L" / " + std::to_wstring((int)MaxHp);
        InGraphics->DrawString(HpText.c_str(), -1, UIFont, Gdiplus::PointF(25, 20), TextBrush);
    }
}

void UIManager::ShowPlayTime(Gdiplus::Graphics* InGraphics)
{
    wchar_t timeText[32];
    swprintf(timeText, 32, L"Time: %.1f s", PlayTime);
    Gdiplus::Font font(L"Arial", 18);
    Gdiplus::SolidBrush textBrush(Gdiplus::Color(255, 255, 255));
    float centerX = GameManager::ScreenWidth * 0.5f - 60.0f;
    InGraphics->DrawString(timeText, -1, &font, Gdiplus::PointF(centerX, 20), &textBrush);
}

void UIManager::ShowEnemyKillCount(Gdiplus::Graphics* InGraphics)
{
    wchar_t killText[32];
    swprintf(killText, 32, L"Enemy: %d", EnemyKillCount);
    float rightX = GameManager::ScreenWidth - 160.0f;
    InGraphics->DrawString(killText, -1, UIFont, Gdiplus::PointF(rightX, 20), TextBrush);
}
