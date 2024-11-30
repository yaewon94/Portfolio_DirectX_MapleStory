#pragma once
#include "Entity.h"
#include "Layer.h"
#include "Component.h"

class Script;
class Transform;
class RenderComponent;

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

public: // TODO : Test Level���� �׽�Ʈ ���� Level Ŭ���������� ȣ���� �� �ְ� �ٲܰ�
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
	T* const GetComponent() const;

	template<typename T> requires std::derived_from<T, Component>
	T* const AddComponent();
	
private:
	void AddComponent(Component* const origin);
};

#include "GameObject.inl"