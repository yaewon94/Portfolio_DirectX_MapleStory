#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "RenderManager.h"
#include "Transform.h"
#include "Script.h"

GameObject::GameObject(const string& name)
	: m_name(name), m_isActive(true), m_layer(0), m_tag(OBJECT_TAG::TAG_DEFAULT)
{
	AddComponent<Transform>();

	// 현재 레벨에 등록
	LevelManager::GetInstance()->RegisterObject(this);
}

GameObject::GameObject(const GameObject& origin) 
{
	*this = origin;

	// 현재 레벨에 등록
	LevelManager::GetInstance()->RegisterObject(this);
}

GameObject::~GameObject()
{
	for (auto& pair : m_componentMap)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}

	for (auto script : m_scripts)
	{
		if (script != nullptr)
		{
			delete script;
			script = nullptr;
		}
	}

	m_tr = nullptr;
	m_renderComponent = nullptr;
}

GameObject& GameObject::operator=(const GameObject& other)
{
	m_name = other.m_name;
	m_isActive = other.m_isActive;
	m_layer = other.m_layer;
	m_tag = other.m_tag;

	for (const auto& pair : other.m_componentMap)
	{
		AddComponent(pair.second);
	}

	for (Script* const script : other.m_scripts)
	{
		m_scripts.push_back(script->Clone(this));
	}

	return *this;
}

void GameObject::Init()
{
	// 메인카메라에 오브젝트 등록
	if (m_renderComponent != nullptr) RenderManager::GetInstance()->AddObject(this);
}

void GameObject::Tick()
{
	if (m_isActive)
	{
		for (Script* const script : m_scripts)
		{
			script->Tick();
		}
	}
}

void GameObject::FinalTick()
{
	if (m_isActive)
	{
		for (const auto& pair : m_componentMap)
		{
			pair.second->FinalTick();
		}

		for (Script* const script : m_scripts)
		{
			script->FinalTick();
		}
	}
}

void GameObject::SetLayer(LAYER layer)
{
	if (m_renderComponent != nullptr)
	{
		RenderManager::GetInstance()->DeleteObject(this);
		m_layer = layer;
		RenderManager::GetInstance()->AddObject(this);
	}
	else
	{
		m_layer = layer;
	}
}

void GameObject::SetTag(OBJECT_TAG tag)
{
	LevelManager::GetInstance()->DeleteObject(this);
	m_tag = tag;
	LevelManager::GetInstance()->RegisterObject(this);
}

void GameObject::AddComponent(Component* const origin)
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