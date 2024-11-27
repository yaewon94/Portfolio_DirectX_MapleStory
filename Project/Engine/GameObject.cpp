#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "RenderManager.h"
#include "Transform.h"

GameObject::GameObject(const string& name)
	: m_name(name), m_layerIdx(0)
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

	m_tr = nullptr;
}

GameObject& GameObject::operator=(const GameObject& other)
{
	m_name = other.m_name;
	m_layerIdx = other.m_layerIdx;
	for (const auto& pair : other.m_componentMap)
	{
		AddComponent(pair.second);
	}

	return *this;
}

void GameObject::Init()
{
	for (const auto& pair : m_componentMap)
	{
		pair.second->Init();
	}

	// 메인카메라에 오브젝트 등록
	if (m_renderComponent != nullptr) RenderManager::GetInstance()->AddObject(this);
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

void GameObject::SetLayer(UINT layer)
{
	if (layer > MAX_LAYER)
	{
		MessageBox(nullptr, L"레이어 값은 32 이하로만 설정할 수 있습니다", L"레이어 변경 실패", MB_OK);
		return;
	}
}