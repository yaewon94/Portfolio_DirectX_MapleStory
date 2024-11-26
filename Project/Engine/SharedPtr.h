#pragma once
#include "pch.h"

// ���� ����Ʈ �����͸� ����� Ŭ������ �������̽�
class IPtrReleasable
{
private:
	UINT refCount;	// �ش� ��ü�� ���� ���� ����Ʈ ������ ��

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
	// ����Ʈ �����ͷθ� ��ü �����ϵ��� ����
	template<typename T> friend class SharedPtr;

	void AddRefCount() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }

	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;
};

// ���� ����Ʈ ������ Ŭ����
template<typename T>
class SharedPtr final
{
private:
	T* t;

public:
	// �ʱ�ȭ �뵵 ���븸��� or ����Ʈ ������ �ִ� ��ü ������ �� ȣ��
	SharedPtr() : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T>) t = new T;
	}

	// args==nullptr�� Ptr(args...) ȣ�� ����
	SharedPtr(nullptr_t) : t(nullptr)
	{
	}

	// @ param : ������ ��ü
	SharedPtr(T* const t) : t(t)
	{
		if (t != nullptr) t->AddRefCount();
	}

	// @ param : ������ ��ü�� ������ �Ķ����
	template<typename... Args>
	SharedPtr(Args... args) : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T, Args...>) t = new T(args...);
#ifdef _DEBUG
		else assert(nullptr);
#endif // _DEBUG
	}

	// ��������� (lValue)
	SharedPtr(const SharedPtr& origin) : t(nullptr)
	{
		*this = origin;
	}

	// ��������� (rValue)
	SharedPtr(SharedPtr&& origin) noexcept : t(nullptr)
	{
		*this = std::move(origin);
	}

	// �Ҹ���
	~SharedPtr()
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}
	}

public:
	// ���Կ����� (lValue)
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

	// ���Կ����� (rValue)
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

	// �� ������ (==)
	bool operator==(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return true;
		else return false;
	}

	// �� ������ (!=)
	bool operator!=(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return false;
		else return true;
	}

	// ������ ���� ������
	T* const operator->() const
	{
#ifdef _DEBUG
		if (t == nullptr) assert(nullptr);
#endif // _DEBUG
		return t;
	}

public:
	// ����ȯ
	template<typename U>
	SharedPtr<U> ptr_dynamic_cast()
	{
		if (dynamic_cast<U*>(t) != nullptr) return SharedPtr<U>((U*)t);
		else return nullptr;
	}

private:
	template<typename U> operator SharedPtr<U>() const = delete; // �ڵ� ����ȯ ����
};