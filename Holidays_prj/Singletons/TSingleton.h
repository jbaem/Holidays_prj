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

	virtual void Initialize() = 0;
	virtual void Destroy() = 0;

protected:
	TSingleton() = default;
	virtual ~TSingleton() = default;

	TSingleton(const TSingleton&) = delete;
	TSingleton& operator=(const TSingleton&) = delete;
	TSingleton(TSingleton&&) = delete;
	TSingleton& operator=(TSingleton&&) = delete;
};
