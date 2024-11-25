#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer()
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
	for (auto obj : other.m_objs)
	{
		m_objs.push_back(obj->Clone());
	}

	return *this;
}

void Layer::Init()
{
	for (auto obj : m_objs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (auto obj : m_objs)
	{
		obj->Tick();
	}
}

void Layer::FinalTick()
{
	for (auto obj : m_objs)
	{
		obj->FinalTick();
	}
}