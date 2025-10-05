#include "InputManager.h"

void InputManager::Initialize()
{
	KeyPressedMap[EKeyState::EKS_Up] = false;
	KeyPressedMap[EKeyState::EKS_Down] = false;
	KeyPressedMap[EKeyState::EKS_Left] = false;
	KeyPressedMap[EKeyState::EKS_Right] = false;
}

void InputManager::Destroy()
{
	KeyPressedMap.clear();
}

void InputManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
	EKeyState KeyState = static_cast<EKeyState>(InKey);
	if (KeyPressedMap.find(KeyState) == KeyPressedMap.end())
		return;

	KeyPressedMap[KeyState] = InIsPressed;
}
