#pragma once
#include "AliveObject.h"

class Monster final : public AliveObject
{
	NO_COPY_MOVE(Monster)

public:
	Monster(GameObject* const owner);
	Monster(const Monster& origin, GameObject* const newOwner);
	~Monster();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;

	virtual void OnCollisionEnter(GameObject* other) final;

private:
	virtual void Move(MOVE_DIRECTION) final {}

private: // GameObject::��������� ���� ȣ��
	virtual Monster* Clone(GameObject* const newOwner) final { return new Monster(*this, newOwner); }
};