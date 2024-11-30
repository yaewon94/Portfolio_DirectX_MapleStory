#pragma once
#include "GameObject.h"
#include "RenderComponent.h"

template<typename T> requires std::derived_from<T, Component>
inline T* const GameObject::GetComponent() const
{
	// Ŀ���� ��ũ��Ʈ Ÿ���� ���
	if constexpr (T::Type == COMPONENT_TYPE::SCRIPT)
	{
		// TODO : �ٸ���� ����
		for (auto script : m_scripts)
		{
			if (dynamic_cast<T*>(script) != nullptr) return (T*)(script);
		}

		return nullptr;
	}
	// ���� �⺻ ������Ʈ�� ���
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
		MessageBox(nullptr, L"�̹� �ش� ������Ʈ�� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
		return nullptr;
	}

	T* component = nullptr;

	// Ŀ���� ��ũ��Ʈ Ÿ��
	if constexpr (T::Type == COMPONENT_TYPE::SCRIPT)
	{
		T* script = new T(this);
		m_scripts.push_back(script);
		return script;
	}
	else
	{
		// ���� �⺻ ������Ʈ
		if constexpr (T::Type == COMPONENT_TYPE::TRANSFORM)
		{
			m_tr = component = new T(this);
		}
		else if constexpr (std::is_base_of_v<RenderComponent, T>)
		{
			if (m_renderComponent != nullptr)
			{
				MessageBox(nullptr, L"�̹� ���� ����Ÿ���� ������Ʈ�� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
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