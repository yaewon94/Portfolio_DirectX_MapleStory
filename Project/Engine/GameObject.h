#pragma once
#include "Entity.h"
#include "Layer.h"
#include "Component.h"

class Script;
class Transform;
class RenderComponent;

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

public: // TODO : Test Level에서 테스트 이후 Level 클래스에서만 호출할 수 있게 바꿀것
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
	T* const GetComponent() const;

	template<typename T> requires std::derived_from<T, Component>
	T* const AddComponent();
	
private:
	void AddComponent(Component* const origin);
};

#include "GameObject.inl"