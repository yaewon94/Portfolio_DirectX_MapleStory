#pragma once
#include "GameObject.h"
#include "RenderComponent.h"

template<typename T> requires std::derived_from<T, Component>
inline T* const GameObject::GetComponent() const
{
	// 커스텀 스크립트 타입인 경우
	if constexpr (T::Type == COMPONENT_TYPE::SCRIPT)
	{
		// TODO : 다른방법 없나
		for (auto script : m_scripts)
		{
			if (dynamic_cast<T*>(script) != nullptr) return (T*)(script);
		}

		return nullptr;
	}
	// 엔진 기본 컴포넌트인 경우
	else
	{
		const auto iter = m_componentMap.find(T::Type);
		if (iter == m_componentMap.end()) return nullptr;

		else return (T*)(iter->second);
	}
}

template<typename T> requires std::derived_from<T, Component>
inline T* const GameObject::AddComponent()
{
	if (GetComponent<T>() != nullptr)
	{
		MessageBox(nullptr, L"이미 해당 컴포넌트가 존재합니다", L"컴포넌트 추가 실패", MB_OK);
		return nullptr;
	}

	T* component = nullptr;

	// 커스텀 스크립트 타입
	if constexpr (T::Type == COMPONENT_TYPE::SCRIPT)
	{
		T* script = new T(this);
		m_scripts.push_back(script);
		return script;
	}
	else
	{
		// 엔진 기본 컴포넌트
		if constexpr (T::Type == COMPONENT_TYPE::TRANSFORM)
		{
			m_tr = component = new T(this);
		}
		else if constexpr (std::is_base_of_v<RenderComponent, T>)
		{
			if (m_renderComponent != nullptr)
			{
				MessageBox(nullptr, L"이미 같은 상위타입의 컴포넌트가 존재합니다", L"컴포넌트 추가 실패", MB_OK);
				return (T*)m_renderComponent;
			}
			m_renderComponent = component = new T(this);
		}
		else if constexpr (T::Type == COMPONENT_TYPE::COLLIDER)
		{
			m_collider = component = new T(this);
		}
		else
		{
			component = new T(this);
		}

		m_componentMap.insert(make_pair(T::Type, component));
		return component;
	}
}