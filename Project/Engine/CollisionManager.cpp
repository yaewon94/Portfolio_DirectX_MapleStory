#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "Transform.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
	InitCollisionCheckTag(OBJECT_TAG::TAG_PLAYER, OBJECT_TAG::TAG_GROUND);
	InitCollisionCheckTag(OBJECT_TAG::TAG_PLAYER_SKILL, OBJECT_TAG::TAG_MONSTER);
}

void CollisionManager::Tick()
{
	// �ٸ� Ÿ���� Tag�� ���� ������Ʈ�� �ݶ��̴����� �浹 üũ
	for (const auto& pair : m_checkTagMap)
	{
		for (OBJECT_TAG tag = TAG_DEFAULT; tag != 0; tag <<= 1)
		{
			if (pair.second & tag)
			{
				CheckCollision(pair.first, tag);
			}
		}
	}
}

void CollisionManager::ResetCollisionState(GameObject* const obj)
{
	if (this == nullptr) return;

	// TODO : for�� �ȵ��� �ٷ�ã�� ���
	for (unordered_set<ULONGLONG>::const_iterator iter = m_collisionSet.begin(); iter != m_collisionSet.end(); ++iter)
	{
		COLLIDER_ID* id = (COLLIDER_ID*)&*iter;
		// ��ǻ�͸��� �� �������� �޶� ������ (��Ʋ����� / �򿣵��)
		//UINT leftID = (*iter) >> 32;
		//UINT rightID = (*iter) & UINT_MAX;

		if (obj->GetID() == id->left)
		{
			GameObject* const other = LevelManager::GetInstance()->FindObject(id->right);
			if(other != nullptr) ChangeCollisionState(obj, other, false);
			return;
		}
		else if(obj->GetID() == id->right)
		{
			GameObject* const other = LevelManager::GetInstance()->FindObject(id->left);
			if(other != nullptr) ChangeCollisionState(other, obj, false);
			return;
		}
	}
}

bool CollisionManager::IsPerfectOverlapped(GameObject* const a, GameObject* const b)
{
	auto A = a->GetTransform()->GetWorldPos() - 0.5 * a->GetTransform()->GetWorldScale();
	auto B = b->GetTransform()->GetWorldPos() - 0.5 * b->GetTransform()->GetWorldScale();
	auto xDiff = A.x - B.x;
	auto yDiff = A.y - B.y;

	if (xDiff*xDiff < 1.f || yDiff*yDiff < 1.f) return true;
	return false;
}

void CollisionManager::InitCollisionCheckTag(OBJECT_TAG a, OBJECT_TAG b)
{
#ifdef _DEBUG
	if (a == b) assert(nullptr);
#endif // _DEBUG
	if (a > b)
	{
		OBJECT_TAG temp = a;
		a = b;
		b = temp;
	}

	auto iter = m_checkTagMap.find(a);
	if (iter != m_checkTagMap.end()) iter->second |= b;
	else m_checkTagMap.insert(make_pair(a, b));
}

void CollisionManager::CheckCollision(OBJECT_TAG tagA, OBJECT_TAG tagB)
{
	for (const auto a : LevelManager::GetInstance()->GetObjects(tagA))
	{
		if (!a->GetCollider()->IsActive()) continue;

		for (const auto b : LevelManager::GetInstance()->GetObjects(tagB))
		{
			if (!b->GetCollider()->IsActive()) continue;
			CheckCollision(a, b);
		}
	}
}

void CollisionManager::CheckCollision(GameObject* const a, GameObject* const b)
{
	static constexpr auto RECT = 4;
	static const Vec3 arrRect[RECT] =
	{
		Vec3(-0.5f, 0.5f, 0.f),
		Vec3(0.5f, 0.5f, 0.f),
		Vec3(0.5f, -0.5f, 0.f),
		Vec3(-0.5f, -0.5f, 0.f)
	};

	const Matrix& matA = a->GetCollider()->GetWorldMatrix();
	const Matrix& matB = b->GetCollider()->GetWorldMatrix();

	// ������(������ ��ų ���) ���ϱ�
	Vec3 arrProj[RECT] = {};
	arrProj[0] = XMVector3TransformCoord(arrRect[1], matA) - XMVector3TransformCoord(arrRect[0], matA);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], matA) - XMVector3TransformCoord(arrRect[0], matA);
	arrProj[2] = XMVector3TransformCoord(arrRect[1], matB) - XMVector3TransformCoord(arrRect[0], matB);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], matB) - XMVector3TransformCoord(arrRect[0], matB);

	// ����������� �� �浹ü�� �߽��� ���� ����
	Vec3 center = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matA) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matB);

	for (UINT i = 0; i < RECT; ++i)
	{
		Vec3 vProj = arrProj[i];
		vProj.Normalize();

		float fCenter = fabs(center.Dot(vProj));
		float fDistance = 0.f;

		for (UINT j = 0; j < RECT; ++j)
		{
			fDistance += fabs(vProj.Dot(arrProj[j]));
		}

		fDistance /= 2.f;

		if (fDistance < fCenter)
		{
			ChangeCollisionState(a, b, false);
			return;
		}
	}

	ChangeCollisionState(a, b, true);
}

void CollisionManager::ChangeCollisionState(GameObject* const a, GameObject* const b, bool isCollision)
{
	COLLIDER_ID id = {};
	id.left = a->GetID();
	id.right = b->GetID();
	unordered_set<ULONGLONG>::const_iterator iter = m_collisionSet.find(id.ID);

	// �̹� ������ �浹
	if (isCollision)
	{
		// ���� �����ӿ� �浹���� ���� ���
		if (iter == m_collisionSet.end())
		{
			m_collisionSet.insert(id.ID);
			a->GetCollider()->OnCollisionEnter(b);
			b->GetCollider()->OnCollisionEnter(a);
		}
		// ���� �����ӿ� �浹�� ���
		else
		{
			a->GetCollider()->OnCollisionTick(b);
			b->GetCollider()->OnCollisionTick(a);
		}
	}
	// �̹� �����ӿ� �浹���� ����
	else
	{
		// ���� �����ӿ� �浹�� ���
		if (iter != m_collisionSet.end())
		{
			m_collisionSet.erase(id.ID);
			a->GetCollider()->OnCollisionExit(b);
			b->GetCollider()->OnCollisionExit(a);
		}
	}
}