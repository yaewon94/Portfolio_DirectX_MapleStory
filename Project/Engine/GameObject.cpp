#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Layer.h"
#include "Transform.h"

GameObject::GameObject(const string& name)
	: m_name(name), m_layerIdx(0)
{
	AddComponent<Transform>();

	// 현재 레벨에 등록
	LevelManager::GetInstance()->AddObject(this);
}

GameObject::GameObject(const GameObject& origin) 
{
	*this = origin;

	// 현재 레벨에 등록
	LevelManager::GetInstance()->AddObject(this);
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
}

GameObject& GameObject::operator=(const GameObject& other)
{
	m_name = other.m_name;
	m_layerIdx = other.m_layerIdx;
	for (const auto& pair : other.m_componentMap)
	{
		m_componentMap.insert(make_pair(pair.first, pair.second->Clone(this)));
	}

	return *this;
}

void GameObject::Init()
{
	for (const auto& pair : m_componentMap)
	{
		pair.second->Init();
	}
}

void GameObject::Tick()
{
}

void GameObject::FinalTick()
{
	for (const auto& pair : m_componentMap)
	{
		pair.second->FinalTick();
	}
}

void GameObject::Render()
{
}

void GameObject::SetLayer(UINT layer)
{
	if (layer > MAX_LAYER)
	{
		MessageBox(nullptr, L"레이어 값은 32 이하로만 설정할 수 있습니다", L"레이어 변경 실패", MB_OK);
		return;
	}
}