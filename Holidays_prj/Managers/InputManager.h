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
	inline const bool IsKeyPressed(EKey KeyState) { return KeyPressedMap[KeyState]; }

	// Getter
	inline EKey GetLastKey() const { return LastKey; }

private:
	virtual ~InputManager() = default;

	EKey LastKey = EKey::EK_NONE;
	std::unordered_map<EKey, bool> KeyPressedMap;
};

