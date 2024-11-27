#include "pch.h"
#include "Level.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "Camera.h"

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
	for (auto& pair : m_layerMap)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

Level& Level::operator=(const Level& other)
{
	m_name = other.m_name;
	for (const auto& pair : other.m_layerMap)
	{
		m_layerMap.insert(make_pair(pair.first, pair.second->Clone()));
	}

	return *this;
}

void Level::Init()
{
	// 필수 오브젝트 추가
	GameObject* obj = LevelManager::GetInstance()->CreateObject("Main Camera");
	obj->AddComponent<Camera>();

	for (const auto& pair : m_layerMap)
	{
		pair.second->Init();
	}
}

void Level::Tick()
{
	for (const auto& pair : m_layerMap)
	{
		pair.second->Tick();
	}
}

void Level::FinalTick()
{
	for (const auto& pair : m_layerMap)
	{
		pair.second->FinalTick();
	}
}

void Level::RegisterObject(GameObject* const obj)
{
#ifdef _DEBUG
	if (obj->GetLayer() > MAX_LAYER) assert(nullptr);
#endif // _DEBUG

	map<LAYER_TYPE, Layer*>::const_iterator iter = m_layerMap.find(obj->GetLayer());

	if (iter != m_layerMap.end())
	{
		iter->second->RegisterObject(obj);
	}
	else
	{
		m_layerMap.insert(make_pair(obj->GetLayer(), new Layer(obj->GetLayer())));
		m_layerMap.find(obj->GetLayer())->second->RegisterObject(obj);
	}
}