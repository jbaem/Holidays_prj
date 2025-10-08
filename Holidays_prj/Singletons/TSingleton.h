#pragma once

template<typename T>
class TSingleton
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}

protected:
	TSingleton() = default;
	virtual ~TSingleton() = default;

	TSingleton(const TSingleton&) = delete;
	TSingleton& operator=(const TSingleton&) = delete;
	TSingleton(TSingleton&&) = delete;
	TSingleton& operator=(TSingleton&&) = delete;
};
