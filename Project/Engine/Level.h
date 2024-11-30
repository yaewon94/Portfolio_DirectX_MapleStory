#pragma once
#include "Entity.h"
#include "GameObjectTag.h"

class GameObject;

// 게임 레벨(==scene) 클래스
class Level : public Entity
{
	friend class LevelManager;

private:
	string m_name;
	unordered_map<OBJECT_TAG, vector<GameObject*>> m_objectMap;

private:
	Level(const string& name);
	Level(const Level& origin);
	~Level();
	Level& operator=(const Level& other);
	virtual Level* Clone() final { return new Level(*this); }

private:
	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();

private:
	GameObject* const FindObject(const UINT ID) const;
	const vector<GameObject*>& GetObjects(OBJECT_TAG tag) const { return m_objectMap.find(tag)->second; }
	void RegisterObject(GameObject* const obj);
	void DeleteObject(GameObject* const obj);
};