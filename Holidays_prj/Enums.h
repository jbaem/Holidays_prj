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

enum class EKey : uint8_t
{
	EK_NONE = 0,

	EK_UP = VK_UP,
	EK_LEFT = VK_LEFT,
	EK_DOWN = VK_DOWN,
	EK_RIGHT = VK_RIGHT,

	EK_SHOOT = 'W',
	EK_JUMP = 'A',
	EK_DASH = 'S',
	EK_ATTACK = 'D'
};

enum class EResourceID
{
	None = 0,
	// Background, Foreground, Decors
	BackGround,
	BackGround1,
	BackGround2,
	BackGround3,
	Decors,

	// Effects
	RedEffect,
	GreenEffect,
	BlueEffect,
	PurpleEffect,

	// Terrain Sprites
	Tileset,
	LeftPlatform,
	MiddlePlatform,
	RightPlatform,

	LeftWall,
	RightWall,
	TopWall
};

enum class EComponentType
{
	None = 0,
	Collider,
	Physics,
	Animator
};

enum class ESceneType
{
	PlayerTest,
	MainMenu,
	Arena,
	GameOver
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
	BackGround,
	Terrain,
	Player,
	Enemy,
	Bullet,
	Misc
};

enum class EPlayerState : uint8_t
{
	Idle,
	Move,
	Crouch,

	Dash,
	Jump,
	Fall,

	Attack1,
	Attack2,
	Shoot,
	
	Hit,
	Death,
};

enum class ELook : uint8_t
{
	Left,
	Right
};

enum class EBlockType : uint8_t
{
	None,
	Solid,
	OneWay	// can pass through from below
};
