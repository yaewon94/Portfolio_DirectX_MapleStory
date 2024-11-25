#pragma once
#include "Entity.h"
#include "Component.h"

class GameObject final : public Entity
{
private:
	string m_name;
	UINT m_layerIdx;
	map<COMPONENT_TYPE, Component*> m_componentMap;

public:
	GameObject(const string& name);
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);
	virtual GameObject* Clone() final { return new GameObject(*this); }

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

public:
	const string& GetName() const { return m_name; }
	void SetName(const string& name) { m_name = name; }

	UINT GetLayer() const { return m_layerIdx; }
	void SetLayer(UINT layer);

	template<typename T> requires std::derived_from<T, Component>
	T* const GetComponent()
	{
		const auto iter = m_componentMap.find(T::Type);
		if (iter == m_componentMap.end()) return nullptr;
		else return (T*)(iter->second);
	}

	template<typename T> requires std::derived_from<T, Component>
	T* const AddComponent()
	{
		if (GetComponent<T>() != nullptr)
		{
			MessageBox(nullptr, L"�̹� �ش� ������Ʈ�� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
			return nullptr;
		}

		m_componentMap.insert(make_pair(T::Type, new T(this)));
		return GetComponent<T>();
	}
};