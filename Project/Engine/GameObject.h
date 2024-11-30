#pragma once
#include "Entity.h"
#include "Component.h"
#include "RenderValues.h"
#include "GameObjectTag.h"

class Script;
class Transform;
class RenderComponent;
class Collider;

// ���ӿ�����Ʈ �����Ҵ�/���� ���������� ���� �������̽�
class IGameObjectDynamicAllocation
{
	friend class LevelManager;
	friend class Level;

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
	bool m_isActive;
	LAYER m_layer;
	OBJECT_TAG m_tag;
	map<COMPONENT_TYPE, Component*> m_componentMap;
	vector<Script*> m_scripts;

	// ���� ������ ���� �ʵ�
	Transform* m_tr;
	RenderComponent* m_renderComponent;
	Collider* m_collider;

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

	bool IsActive() const { return m_isActive; }
	void SetActive(bool isActive) { m_isActive = isActive; }

	LAYER GetLayer() const { return m_layer; }
	void SetLayer(LAYER layer);

	OBJECT_TAG GetTag() const { return m_tag; }
	void SetTag(OBJECT_TAG tag);

	Transform* const GetTransform() const { return m_tr; }
	RenderComponent* const GetRenderComponent() const { return m_renderComponent; }
	Collider* const GetCollider() const { return m_collider; }

	template<typename T> requires std::derived_from<T, Component>
	T* const GetComponent() const;

	template<typename T> requires std::derived_from<T, Component>
	T* const AddComponent();
	
private:
	void AddComponent(Component* const origin);
};

#include "GameObject.inl"