#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer(UINT index) 
	: m_idx(index)
{
}

Layer::Layer(const Layer& origin)
{
	*this = origin;
}

Layer::~Layer()
{
	for (auto obj : m_objs)
	{
		if (obj != nullptr)
		{
			delete obj;
			obj = nullptr;
		}
	}
}

Layer& Layer::operator=(const Layer& other)
{
	m_idx = other.m_idx;

	for (const auto obj : other.m_objs)
	{
		m_objs.push_back(obj->Clone());
	}

	return *this;
}

void Layer::Init()
{
	for (const auto obj : m_objs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (const auto obj : m_objs)
	{
		obj->Tick();
	}
}

void Layer::FinalTick()
{
	for (const auto obj : m_objs)
	{
		obj->FinalTick();
	}
}

void Layer::AddObject(GameObject* const obj)
{
#ifdef _DEBUG
	if (obj->GetLayer() != m_idx) assert(nullptr);
#endif // _DEBUG

	// 중복체크
	for (const GameObject* const _obj : m_objs)
	{
		if (_obj == obj)
		{
			MessageBox(nullptr, L"이미 등록된 오브젝트 입니다", L"게임오브젝트 추가 실패", MB_OK);
			return;
		}
	}

	m_objs.push_back(obj);
}