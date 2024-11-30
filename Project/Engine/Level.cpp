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
	for (const auto& pair : m_objectMap)
	{
		for (auto obj : pair.second)
		{
			if (obj != nullptr)
			{
				delete obj;
				obj = nullptr;
			}
		}
	}
}

Level& Level::operator=(const Level& other)
{
	m_name = other.m_name;

	for (const auto& pair : other.m_objectMap)
	{
		if(m_objectMap.find(pair.first) == m_objectMap.end()) m_objectMap.insert(make_pair(pair.first, vector<GameObject*>()));
		auto& vec = m_objectMap.find(pair.first)->second;
		for (auto originObj : pair.second)
		{
			vec.push_back(originObj->Clone());
		}
	}

	return *this;
}

void Level::Init()
{
	// 필수 오브젝트 추가
	GameObject* obj = LevelManager::GetInstance()->CreateObject("Main Camera");
	obj->AddComponent<Camera>();

	for (const auto& pair : m_objectMap)
	{
		for (const auto obj : pair.second)
		{
			obj->Init();
		}
	}
}

void Level::Tick()
{
	for (const auto& pair : m_objectMap)
	{
		for (const auto obj : pair.second)
		{
			obj->Tick();
		}
	}
}

void Level::FinalTick()
{
	for (const auto& pair : m_objectMap)
	{
		for (const auto obj : pair.second)
		{
			obj->FinalTick();
		}
	}
}

GameObject* const Level::FindObject(const UINT ID) const
{
	for (const auto& pair : m_objectMap)
	{
		for (auto obj : pair.second)
		{
			if (ID == obj->GetID()) return obj;
		}
	}
	return nullptr;
}

void Level::RegisterObject(GameObject* const obj)
{
	auto iter = m_objectMap.find(obj->GetTag());

	if (iter != m_objectMap.end())
	{
#ifdef _DEBUG
		for (auto _obj : iter->second)
		{
			if (obj == _obj) assert(nullptr);	// 중복
		}
#endif // _DEBUG
		iter->second.push_back(obj);
	}
	else
	{
		m_objectMap.insert(make_pair(obj->GetTag(), vector<GameObject*>()));
		m_objectMap.find(obj->GetTag())->second.push_back(obj);
	}
}

void Level::DeleteObject(GameObject* const obj)
{
	auto mapiter = m_objectMap.find(obj->GetTag());
	if (mapiter != m_objectMap.end())
	{
		for (auto veciter = mapiter->second.begin(); veciter != mapiter->second.end(); ++veciter)
		{
			if (obj == *veciter)
			{
				mapiter->second.erase(veciter);
				if (mapiter->second.empty()) m_objectMap.erase(mapiter);
				return;
			}
		}
#ifdef _DEBUG
		assert(nullptr); // 지우려는 오브젝트가 애초에 등록이 안되어있음
#endif // _DEBUG

	}
#ifdef _DEBUG
	else assert(nullptr); // 지우려는 오브젝트가 애초에 등록이 안되어있음
#endif // _DEBUG
}