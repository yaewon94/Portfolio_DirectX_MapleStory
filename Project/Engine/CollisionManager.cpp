#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "LevelManager.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
	InitCollisionCheckTag(OBJECT_TAG::TAG_PLAYER, OBJECT_TAG::TAG_GROUND);
}

void CollisionManager::Tick()
{
	// 다른 타입의 Tag에 속한 오브젝트의 콜라이더끼리 충돌 체크
	for (const auto& pair : m_checkTagMap)
	{
		for (OBJECT_TAG tag = TAG_DEFAULT; tag < OBJECT_TAG::TAG_END; ++tag)
		{
			if (pair.second & (1 << tag))
			{
				CheckCollision(pair.first, tag);
			}
		}
	}
}

void CollisionManager::ResetCollisionState(GameObject* const obj)
{
	for (unordered_set<ULONGLONG>::const_iterator iter = m_collisionSet.begin(); iter != m_collisionSet.end(); ++iter)
	{
		UINT leftID = (*iter) >> 16;
		UINT rightID = (*iter) & UINT_MAX;

		if (obj->GetID() == leftID)
		{
			GameObject* const other = LevelManager::GetInstance()->FindObject(rightID);
			if(other != nullptr) ChangeCollisionState(obj, other, false);
			return;
		}
		else if(obj->GetID() == rightID)
		{
			GameObject* const other = LevelManager::GetInstance()->FindObject(leftID);
			if(other != nullptr) ChangeCollisionState(nullptr, obj, false);
			return;
		}
	}
}

void CollisionManager::InitCollisionCheckTag(OBJECT_TAG a, OBJECT_TAG b)
{
#ifdef _DEBUG
	if (a == b) assert(nullptr);
#endif // _DEBUG
	if (b > a)
	{
		OBJECT_TAG temp = a;
		a = b;
		b = temp;
	}

	auto iter = m_checkTagMap.find(a);
	if (iter != m_checkTagMap.end()) iter->second |= (1 << b);
	else m_checkTagMap.insert(make_pair(a, 1 << b));
}

void CollisionManager::CheckCollision(OBJECT_TAG tagA, OBJECT_TAG tagB)
{
	for (const auto a : LevelManager::GetInstance()->GetObjects(tagA))
	{
		if (!a->IsActive()) continue;

		for (const auto b : LevelManager::GetInstance()->GetObjects(tagB))
		{
			if (!b->IsActive()) continue;
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

	// 투영축(투영을 시킬 대상) 구하기
	Vec3 arrProj[RECT] = {};
	arrProj[0] = XMVector3TransformCoord(arrRect[1], matA) - XMVector3TransformCoord(arrRect[0], matA);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], matA) - XMVector3TransformCoord(arrRect[0], matA);
	arrProj[2] = XMVector3TransformCoord(arrRect[1], matB) - XMVector3TransformCoord(arrRect[0], matB);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], matB) - XMVector3TransformCoord(arrRect[0], matB);

	// 월드공간에서 두 충돌체의 중심을 이은 벡터
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

	// 이번 프레임 충돌
	if (isCollision)
	{
		// 저번 프레임에 충돌하지 않은 경우
		if (iter == m_collisionSet.end())
		{
			m_collisionSet.insert(id.ID);
			// TODO : 콜백 호출
		}
		// 저번 프레임에 충돌한 경우
		else
		{
			// TODO : 콜백 호출
		}
	}
	// 이번 프레임에 충돌하지 않음
	else
	{
		// 저번 프레임에 충돌한 경우
		if (iter != m_collisionSet.end())
		{
			// TODO : 콜백 호출
			m_collisionSet.erase(id.ID);
		}
	}
}