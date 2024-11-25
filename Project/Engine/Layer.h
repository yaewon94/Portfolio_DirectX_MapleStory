#pragma once
#include "Entity.h"

class GameObject;

// 게임오브젝트의 렌더링 순서, 렌더링 여부 등을 결정
class Layer final : public Entity
{
private:
	vector<GameObject*> m_objs;

public:
	Layer();
	Layer(const Layer& origin);
	~Layer();
	Layer& operator=(const Layer& other);
	virtual Layer* Clone() final { return new Layer(*this); }

public:
	void Init();
	void Tick();
	void FinalTick();
};

#define MAX_LAYER 32