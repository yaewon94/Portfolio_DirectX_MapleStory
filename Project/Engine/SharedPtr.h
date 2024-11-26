#pragma once
#include "pch.h"

// 공유 스마트 포인터를 사용할 클래스의 인터페이스
class IPtrReleasable
{
private:
	UINT refCount;	// 해당 개체를 참조 중인 스마트 포인터 수

protected:
	IPtrReleasable() : refCount(1) {}

	IPtrReleasable(const IPtrReleasable& origin)
	{
		*this = origin;
	}

	IPtrReleasable(IPtrReleasable&& origin) noexcept
	{
		*this = std::move(origin);
	}

	virtual ~IPtrReleasable()
	{
		if (refCount > 0) assert(nullptr);
	}

	IPtrReleasable& operator=(const IPtrReleasable& other)
	{
		refCount = 1;
		return *this;
	}

	IPtrReleasable& operator=(IPtrReleasable&& other) noexcept
	{
		other.refCount = 0;
		refCount = 1;
		return *this;
	}

private:
	// 스마트 포인터로만 객체 생성하도록 강제
	template<typename T> friend class SharedPtr;

	void AddRefCount() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }

	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;
};

// 공유 스마트 포인터 클래스
template<typename T>
class SharedPtr final
{
private:
	T* t;

public:
	// 초기화 용도 깡통만들기 or 디폴트 생성자 있는 객체 생성할 때 호출
	SharedPtr() : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T>) t = new T;
	}

	// args==nullptr인 Ptr(args...) 호출 방지
	SharedPtr(nullptr_t) : t(nullptr)
	{
	}

	// @ param : 참조할 객체
	SharedPtr(T* const t) : t(t)
	{
		if (t != nullptr) t->AddRefCount();
	}

	// @ param : 생성할 객체의 생성자 파라미터
	template<typename... Args>
	SharedPtr(Args... args) : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T, Args...>) t = new T(args...);
#ifdef _DEBUG
		else assert(nullptr);
#endif // _DEBUG
	}

	// 복사생성자 (lValue)
	SharedPtr(const SharedPtr& origin) : t(nullptr)
	{
		*this = origin;
	}

	// 복사생성자 (rValue)
	SharedPtr(SharedPtr&& origin) noexcept : t(nullptr)
	{
		*this = std::move(origin);
	}

	// 소멸자
	~SharedPtr()
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}
	}

public:
	// 대입연산자 (lValue)
	SharedPtr& operator=(const SharedPtr& other)
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		if (other.t != nullptr)
		{
			t = other.t;
			t->AddRefCount();
		}

		return *this;
	}

	// 대입연산자 (rValue)
	SharedPtr& operator=(SharedPtr&& other) noexcept
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		if (other.t != nullptr)
		{
			t = other.t;
			t->AddRefCount();

			other.t->Release();
			other.t = nullptr;
		}

		return *this;
	}

	// 비교 연산자 (==)
	bool operator==(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return true;
		else return false;
	}

	// 비교 연산자 (!=)
	bool operator!=(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return false;
		else return true;
	}

	// 포인터 참조 연산자
	T* const operator->() const
	{
#ifdef _DEBUG
		if (t == nullptr) assert(nullptr);
#endif // _DEBUG
		return t;
	}

public:
	// 형변환
	template<typename U>
	SharedPtr<U> ptr_dynamic_cast()
	{
		if (dynamic_cast<U*>(t) != nullptr) return SharedPtr<U>((U*)t);
		else return nullptr;
	}

private:
	template<typename U> operator SharedPtr<U>() const = delete; // 자동 형변환 방지
};