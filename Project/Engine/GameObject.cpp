#include "pch.h"
#include "GameObject.h"
#include "Layer.h"

GameObject::GameObject() 
	: m_layerIdx(0)
{
}

GameObject::GameObject(const GameObject& origin) 
{
	*this = origin;
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

void GameObject::SetLayer(UINT layer)
{
	if (layer > MAX_LAYER)
	{
		MessageBox(nullptr, L"���̾� ���� 32 ���Ϸθ� ������ �� �ֽ��ϴ�", L"���̾� ���� ����", MB_OK);
		return;
	}
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