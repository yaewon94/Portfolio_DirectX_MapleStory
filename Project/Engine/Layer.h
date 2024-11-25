#pragma once
#include "Entity.h"

class GameObject;

// 게임오브젝트의 렌더링 순서, 렌더링 여부 등을 결정
class Layer final : public Entity
{
	friend class Level;

private:
	UINT m_idx;
	vector<GameObject*> m_objs;

private:
	Layer(UINT index);
	Layer(const Layer& origin);
	~Layer();
	Layer& operator=(const Layer& other);
	virtual Layer* Clone() final { return new Layer(*this); }

private:
	void Init();
	void Tick();
	void FinalTick();

private:
	void AddObject(GameObject* const obj);
};

#define MAX_LAYER 32