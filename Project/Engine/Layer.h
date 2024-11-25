#pragma once
#include "Entity.h"

class GameObject;

// 게임오브젝트의 렌더링 순서, 렌더링 여부 등을 결정
class Layer final : public Entity
{
	NO_COPY_MOVE(Layer);

private:
	vector<GameObject*> m_objs;

public:
	Layer();
	~Layer();

public:
	void Init();
	void Tick();
	void FinalTick();

private:
	virtual Entity* Clone() final { return nullptr; } // delete
};

#define MAX_LAYER 32