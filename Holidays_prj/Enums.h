#pragma once

#include <Windows.h>
#include <cstdint>

enum class GameState : uint8_t
{
	Menu,
	Playing,
	GameOver
};

enum class EKeyState : uint8_t
{
	None = 0,
	EKS_Up = VK_UP,
	EKS_Left = VK_LEFT,
	EKS_Down = VK_DOWN,
	EKS_Right = VK_RIGHT,

	EKS_W = 'W',
	EKS_A = 'A',
	EKS_S = 'S',
	EKS_D = 'D'
};

enum class EResourceID
{
	None = 0,
	Player,
	PlayerIdle
};

enum class EPhysicsLayer
{
	None = 0,
	Terrain,
	Pawn,
	Player,
	Enemy
};

enum class ERenderLayer
{
	None = 0,
	BackGround,
	Terrain,
	Player,
	Enemy,
	Bullet,
	Misc
};

enum class EPlayerState
{
	None = 0,
	Idle,
	Move,
	Dash,
	Jump,
	Attack,
	Defense,
	Damaged
};

enum class EComponentType
{
	None = 0,
	Collider,
	Physics
};
