#include "InputManager.h"

void InputManager::Initialize()
{
	KeyPressedMap[EKey::EK_UP] = false;
	KeyPressedMap[EKey::EK_LEFT] = false;
	KeyPressedMap[EKey::EK_DOWN] = false;
	KeyPressedMap[EKey::EK_RIGHT] = false;

	KeyPressedMap[EKey::EK_SHOOT] = false;
	KeyPressedMap[EKey::EK_JUMP] = false;
	KeyPressedMap[EKey::EK_DASH] = false;
	KeyPressedMap[EKey::EK_ATTACK] = false;

	LastKey = EKey::EK_NONE;
}

void InputManager::Destroy()
{
	KeyPressedMap.clear();
}

void InputManager::HandleKeyState(WPARAM InKey, bool bIsPressed)
{
	EKey KeyState = static_cast<EKey>(InKey);
	if (KeyPressedMap.find(KeyState) == KeyPressedMap.end())
		return;

	KeyPressedMap[KeyState] = bIsPressed;

	LastKey = bIsPressed ? KeyState : EKey::EK_NONE;
}
