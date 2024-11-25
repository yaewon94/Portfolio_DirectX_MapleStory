#pragma once

typedef void(*EXIT)(void);

template<typename T>
class Singleton
{
private:
	static T* m_Instance;

public:
	static T* const GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new T;
			atexit((EXIT)&Singleton<T>::Destroy);
		}

		return m_Instance;
	}

private:
	static void Destroy()
	{
		if (m_Instance != nullptr)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
};

template<typename T>
T* Singleton<T>::m_Instance = nullptr;

#define NO_COPY_MOVE(Type) private:\
							Type(const Type&) = delete;\
							Type(Type&&) = delete;\
							Type& operator=(const Type&) = delete;\
							Type& operator=(Type&&) = delete;

#define SINGLETON(Type) private:\
						Type();\
						~Type();\
						NO_COPY_MOVE(Type)\
						friend class Singleton<Type>;