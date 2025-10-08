#pragma once

#include <Windows.h>
#include <cstdint>

enum class GameState : uint8_t
{
	PlayerTest,
	MainMenu,
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
	BackGround,
	BackGround1,
	BackGround2,
	BackGround3,
	PlayerIdle,
	PlayerMove
};

enum class EPhysicsLayer : uint32_t
{
	None			= 0,
	Terrain			= 1 << 0,
	Pawn			= 1 << 1,
	Player			= 1 << 2,
	Enemy			= 1 << 3,
	PlayerBullet	= 1 << 4,
	EnemyBullet		= 1 << 5,
	All				= 0xFFFFFFFF
};
inline EPhysicsLayer operator|(EPhysicsLayer a, EPhysicsLayer b)
{
	return static_cast<EPhysicsLayer>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

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


enum class ESceneType
{
	PlayerTest,
	MainMenu,
	Stage1
};

enum class EPlayerDirection : uint8_t
{
	Left,
	Right
};