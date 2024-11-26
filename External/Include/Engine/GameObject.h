#pragma once
#include "Entity.h"
#include "Component.h"
#include "RenderComponent.h"

class Transform;

// 게임오브젝트
class GameObject final : public Entity
{
private:
	string m_name;
	UINT m_layerIdx;
	map<COMPONENT_TYPE, Component*> m_componentMap;

	// 빠른 접근을 위한 필드
	Transform* m_tr;
	RenderComponent* m_renderComponent;

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

	Transform* const GetTransform() const { return m_tr; }

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

		T* component = nullptr;

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
		else
		{
			component = new T(this);
		}

		m_componentMap.insert(make_pair(T::Type, component));
		return component;
	}
	
private:
	void AddComponent(Component* const origin)
	{
#ifdef _DEBUG
		if (m_componentMap.find(origin->GetType()) != m_componentMap.end()) assert(nullptr);
#endif // _DEBUG

		Component* clone = nullptr;

		if (origin->GetType() == COMPONENT_TYPE::TRANSFORM)
		{
			clone = origin->Clone(this);
			m_tr = (Transform*)clone;
		}
		else if (dynamic_cast<RenderComponent*>(clone) != nullptr)
		{
#ifdef _DEBUG
			if (m_renderComponent != nullptr) assert(nullptr);
#endif // _DEBUG
			clone = origin->Clone(this);
			m_renderComponent = (RenderComponent*)clone;
		}
		else
		{
			clone = origin->Clone(this);
		}

		m_componentMap.insert(make_pair(clone->GetType(), clone));
	}
};