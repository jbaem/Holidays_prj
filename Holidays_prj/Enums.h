#pragma once

#include <Windows.h>
#include <cstdint>

enum class GameState : uint8_t
{
	Playing,
	GameOver
};

enum class EKeyState : uint8_t
{
	None = 0,
	EKS_Up = VK_UP,
	EKS_Down = VK_DOWN,
	EKS_Left = VK_LEFT,
	EKS_Right = VK_RIGHT
};

enum class ResourceID
{
	None,
	Player
};