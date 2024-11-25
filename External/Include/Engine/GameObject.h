#pragma once
#include "Entity.h"

class GameObject final : public Entity
{
private:
	string m_name;
	UINT m_layerIdx;

public:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);
	virtual GameObject* Clone() final { return new GameObject(*this); }

public:
	const string& GetName() { return m_name; }
	void SetName(const string& name) { m_name = name; }

	void SetLayer(UINT layer);
	UINT GetLayer() { return m_layerIdx; }

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
};