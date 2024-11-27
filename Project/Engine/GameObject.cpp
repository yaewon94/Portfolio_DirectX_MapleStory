#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "RenderManager.h"
#include "Transform.h"
#include "Script.h"

GameObject::GameObject(const string& name)
	: m_name(name), m_layerIdx(0)
{
	AddComponent<Transform>();

	// ���� ������ ���
	LevelManager::GetInstance()->RegisterObject(this);
}

GameObject::GameObject(const GameObject& origin) 
{
	*this = origin;

	// ���� ������ ���
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
	m_layerIdx = other.m_layerIdx;

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
	for (const auto& pair : m_componentMap)
	{
		pair.second->Init();
	}

	for (Script* const script : m_scripts)
	{
		script->Init();
	}

	// ����ī�޶� ������Ʈ ���
	if (m_renderComponent != nullptr) RenderManager::GetInstance()->AddObject(this);
}

void GameObject::Tick()
{
	for (Script* const script : m_scripts)
	{
		script->Tick();
	}
}

void GameObject::FinalTick()
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