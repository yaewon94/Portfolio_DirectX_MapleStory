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
			MessageBox(nullptr, L"이미 해당 컴포넌트가 존재합니다", L"컴포넌트 추가 실패", MB_OK);
			return nullptr;
		}

		m_componentMap.insert(make_pair(T::Type, new T(this)));
		return GetComponent<T>();
	}
};