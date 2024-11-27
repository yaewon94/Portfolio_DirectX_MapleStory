#pragma once
#include "Entity.h"
#include "Layer.h"
#include "Component.h"
#include "RenderComponent.h"

class Transform;
class Script;

// ���ӿ�����Ʈ �����Ҵ�/���� ���������� ���� �������̽�
class IGameObjectDynamicAllocation
{
	friend class Layer;
	friend class LevelManager;

protected:
	virtual ~IGameObjectDynamicAllocation() {}
	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;
};

// ���ӿ�����Ʈ
class GameObject final : public Entity, public IGameObjectDynamicAllocation
{
private:
	string m_name;
	LAYER_TYPE m_layerIdx;
	map<COMPONENT_TYPE, Component*> m_componentMap;
	vector<Script*> m_scripts;

	// ���� ������ ���� �ʵ�
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

public:
	const string& GetName() const { return m_name; }
	void SetName(const string& name) { m_name = name; }

	LAYER_TYPE GetLayer() const { return m_layerIdx; }
	void SetLayer(LAYER_TYPE layer)
	{
		if (layer > MAX_LAYER)
		{
			wstring msg = L"���̾� ���� " + std::to_wstring(MAX_LAYER) + L" ���Ϸθ� ������ �� �ֽ��ϴ�";
			MessageBox(nullptr, msg.c_str(), L"���̾� ���� ����", MB_OK);
			return;
		}

		m_layerIdx = layer;
	}

	Transform* const GetTransform() const { return m_tr; }
	RenderComponent* const GetRenderComponent() const { return m_renderComponent; }

	template<typename T> requires std::derived_from<T, Component>
	T* const GetComponent()
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
	T* const AddComponent()
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
			else
			{
				component = new T(this);
			}

			m_componentMap.insert(make_pair(T::Type, component));
			return component;
		}
	}
	
private:
	void AddComponent(Component* const origin)
	{
#ifdef _DEBUG
		if (origin->GetType() == COMPONENT_TYPE::SCRIPT) assert(nullptr); // = �����ڿ��� �ٷ� Clone() ȣ���ؼ� �����ϱ�
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