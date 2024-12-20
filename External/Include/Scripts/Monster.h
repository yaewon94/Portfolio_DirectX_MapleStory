#pragma once
#include "AliveObject.h"

class Monster final : public AliveObject
{
	NO_COPY_MOVE(Monster)

public:
	Monster(GameObject* const owner);
	Monster(const Monster& origin, GameObject* const newOwner);
	~Monster();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;

	virtual void OnCollisionTick(GameObject* other) final;

private:
	virtual void Move(MOVE_DIRECTION) final {}

private: // GameObject::복사생성자 에서 호출
	virtual Monster* Clone(GameObject* const newOwner) final { return new Monster(*this, newOwner); }
};

//////////////////////////////////////////////////////////
// Monster.inl
//////////////////////////////////////////////////////////
#include "Engine/CollisionManager.h"
#include "AttackSkillComponent.h"
inline void Monster::OnCollisionTick(GameObject* other)
{
	if (other->GetTag() & OBJECT_TAG::TAG_PLAYER_SKILL)
	{
		if(CollisionManager::GetInstance()->IsPerfectOverlapped(GetOwner(), other))
		{
			other->GetComponent<FSM>()->ChangeState(STATE_TYPE::HIT);
			ChangeHP(other->GetComponent<AttackSkillComponent>()->GetDamage());
		}
	}
}