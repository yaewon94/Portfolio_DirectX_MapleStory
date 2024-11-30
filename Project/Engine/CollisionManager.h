#pragma once
#include "GameObjectTag.h"

class Collider;
class GameObject;

// 오브젝트 충돌 처리 담당 클래스
class CollisionManager final : public Singleton<CollisionManager>
{
	SINGLETON(CollisionManager);

private:
	// 충돌한 두 Collider의 ID
	union COLLIDER_ID
	{
		struct
		{
			UINT left, right;
		};

		ULONGLONG ID;
	};

private:
	map<OBJECT_TAG, OBJECT_TAGS> m_checkTagMap; // 충돌체크할 OBJECT_TAG 조합
	unordered_set<ULONGLONG> m_collisionSet; // 충돌한 두 콜라이더의 ID

public:
	void Init();
	void Tick();

public:
	void ResetCollisionState(GameObject* const obj);

private:
	void InitCollisionCheckTag(OBJECT_TAG a, OBJECT_TAG b);
	void CheckCollision(OBJECT_TAG tagA, OBJECT_TAG tagB);
	void CheckCollision(GameObject* const a, GameObject* const b);
	void ChangeCollisionState(GameObject* const a, GameObject* const b, bool isCollision);
};