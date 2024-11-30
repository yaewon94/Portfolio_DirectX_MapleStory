#pragma once
#include "GameObjectTag.h"

class Collider;
class GameObject;

// ������Ʈ �浹 ó�� ��� Ŭ����
class CollisionManager final : public Singleton<CollisionManager>
{
	SINGLETON(CollisionManager);

private:
	// �浹�� �� Collider�� ID
	union COLLIDER_ID
	{
		struct
		{
			UINT left, right;
		};

		ULONGLONG ID;
	};

private:
	map<OBJECT_TAG, OBJECT_TAGS> m_checkTagMap; // �浹üũ�� OBJECT_TAG ����
	unordered_set<ULONGLONG> m_collisionSet; // �浹�� �� �ݶ��̴��� ID

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