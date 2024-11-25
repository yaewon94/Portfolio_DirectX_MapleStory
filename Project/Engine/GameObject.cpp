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
		MessageBox(nullptr, L"레이어 값은 32 이하로만 설정할 수 있습니다", L"레이어 변경 실패", MB_OK);
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