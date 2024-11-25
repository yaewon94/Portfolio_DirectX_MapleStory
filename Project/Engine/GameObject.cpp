#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Layer.h"

GameObject::GameObject(const string& name)
	: m_name(name), m_layerIdx(0)
{
	// ���� ������ ���
	LevelManager::GetInstance()->AddObject(this);
}

GameObject::GameObject(const GameObject& origin) 
{
	*this = origin;

	// ���� ������ ���
	LevelManager::GetInstance()->AddObject(this);
}

GameObject::~GameObject()
{
}

GameObject& GameObject::operator=(const GameObject& other)
{
	m_name = other.m_name;
	m_layerIdx = other.m_layerIdx;

	return *this;
}

void GameObject::Init()
{
}

void GameObject::Tick()
{
}

void GameObject::FinalTick()
{
}

void GameObject::Render()
{
}

void GameObject::SetLayer(UINT layer)
{
	if (layer > MAX_LAYER)
	{
		MessageBox(nullptr, L"���̾� ���� 32 ���Ϸθ� ������ �� �ֽ��ϴ�", L"���̾� ���� ����", MB_OK);
		return;
	}
}