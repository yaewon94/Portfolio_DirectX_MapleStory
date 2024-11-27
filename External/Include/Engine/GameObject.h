#pragma once
#include "Entity.h"
#include "Layer.h"
#include "Component.h"
#include "RenderComponent.h"

class Transform;
class Script;

// 게임오브젝트 동적할당/해제 접근제한을 위한 인터페이스
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

// 게임오브젝트
class GameObject final : public Entity, public IGameObjectDynamicAllocation
{
private:
	string m_name;
	LAYER_TYPE m_layerIdx;
	map<COMPONENT_TYPE, Component*> m_componentMap;
	vector<Script*> m_scripts;

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

public:
	const string& GetName() const { return m_name; }
	void SetName(const string& name) { m_name = name; }

	LAYER_TYPE GetLayer() const { return m_layerIdx; }
	void SetLayer(LAYER_TYPE layer)
	{
		if (layer > MAX_LAYER)
		{
			wstring msg = L"레이어 값은 " + std::to_wstring(MAX_LAYER) + L" 이하로만 설정할 수 있습니다";
			MessageBox(nullptr, msg.c_str(), L"레이어 변경 실패", MB_OK);
			return;
		}

		m_layerIdx = layer;
	}

	Transform* const GetTransform() const { return m_tr; }
	RenderComponent* const GetRenderComponent() const { return m_renderComponent; }

	template<typename T> requires std::derived_from<T, Component>
	T* const GetComponent()
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
	T* const AddComponent()
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
		if (origin->GetType() == COMPONENT_TYPE::SCRIPT) assert(nullptr); // = 연산자에서 바로 Clone() 호출해서 생성하기
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