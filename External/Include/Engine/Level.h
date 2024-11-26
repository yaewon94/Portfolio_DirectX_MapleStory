#pragma once
#include "Entity.h"

#include "Layer.h"

class GameObject;

// 게임 레벨(==scene) 클래스
class Level : public Entity
{
	friend class LevelManager;

private:
	string m_name;
	map<LAYER_TYPE, Layer*> m_layerMap;

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
	void RegisterObject(GameObject* const obj);
};