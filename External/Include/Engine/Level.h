#pragma once
#include "Entity.h"

class Layer;

// ���� ����(==scene) Ŭ����
class Level : public Entity
{
	friend class LevelManager;

private:
	string m_name;
	vector<Layer*> m_layers;

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
};