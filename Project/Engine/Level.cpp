#include "pch.h"
#include "Level.h"
#include "Layer.h"

Level::Level(const string& name) 
	: m_name(name)
{
}

Level::Level(const Level& origin)
{
	*this = origin;
}

Level::~Level()
{
	for (auto layer : m_layers)
	{
		if (layer != nullptr)
		{
			delete layer;
			layer = nullptr;
		}
	}
}

Level& Level::operator=(const Level& other)
{
	m_name = other.m_name;
	for (auto layer : other.m_layers)
	{
		m_layers.push_back(layer->Clone());
	}

	return *this;
}

void Level::Init()
{
	for (auto layer : m_layers)
	{
		layer->Init();
	}
}

void Level::Tick()
{
	for (auto layer : m_layers)
	{
		layer->Tick();
	}
}

void Level::FinalTick()
{
	for (auto layer : m_layers)
	{
		layer->FinalTick();
	}
}