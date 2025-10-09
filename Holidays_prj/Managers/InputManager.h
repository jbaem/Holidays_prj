#pragma once

#include <unordered_map>

#include "TSingleton.h"

#include "../Enums.h"

class InputManager : public TSingleton<InputManager>
{
	friend class TSingleton<InputManager>;
public:
	virtual void Initialize();
	virtual void Destroy();

	void HandleKeyState(WPARAM InKey, bool InIsPressed);
	inline const bool IsKeyPressed(EKeyState KeyState) { return KeyPressedMap[KeyState]; }

	// Getter
	inline EKeyState GetLastKey() const { return LastKey; }

private:
	virtual ~InputManager() = default;

	EKeyState LastKey = EKeyState::None;
	std::unordered_map<EKeyState, bool> KeyPressedMap;
};

