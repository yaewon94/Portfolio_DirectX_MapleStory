#pragma once
#include "Component.h"

// 상수버퍼 연동 구조체
struct CB_Transform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;

	Matrix	matWV; // world * view
	Matrix	matWVP; // world * view * projection
};

// 방향 타입
enum DIRECTION_TYPE : byte
{
	DIR_RIGHT, DIR_UP, DIR_FRONT, DIRECTION_TYPE_COUNT_END
};

extern CB_Transform g_tr;

// 게임오브젝트 좌표, 크기, 각도 정보
class Transform final : public Component
{
	NO_COPY_MOVE(Transform)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::TRANSFORM)

private:
	Vec3 m_localPos, m_localScale, m_localRotation;
	Matrix m_matWorld;

	array<Vec3, DIRECTION_TYPE_COUNT_END> m_localDir, m_worldDir;

private:
	enum CHANGE_VALUE : byte
	{
		ON_CHANGE_POS_SCALE = 1,
		ON_CHANGE_ROTATION = ON_CHANGE_POS_SCALE << 1,

		IS_CHANGED_VALUE = ON_CHANGE_POS_SCALE | ON_CHANGE_ROTATION
	};

	byte m_isChangedValue; 	// CHANGE_VALUE 값들 | 연산으로 조합

public:
	Transform(GameObject* const owner);
	Transform(const Transform& origin, GameObject* const newOwner);
	~Transform();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;
	virtual void FinalTick() final;

public:
	void Binding();

public:
	Vec3 GetLocalPos() const { return m_localPos; }
	void SetLocalPos(const Vec3& pos) { m_localPos = pos; m_isChangedValue |= ON_CHANGE_POS_SCALE; }

	Vec3 GetLocalScale() const { return m_localScale; }
	void SetLocalScale(const Vec3& scale) { m_localScale = scale; m_isChangedValue |= ON_CHANGE_POS_SCALE; }

	Vec3 GetLocalRotation() const { return m_localRotation; }
	void SetLocalRotation(const Vec3& rotation) { m_localRotation = rotation; m_isChangedValue |= ON_CHANGE_ROTATION; }

	const Vec3& GetWorldDirection(DIRECTION_TYPE type)
	{
#ifdef _DEBUG
		if (type >= DIRECTION_TYPE_COUNT_END) assert(nullptr);
#endif // _DEBUG
		return m_worldDir[type];
	}

private:
	virtual Transform* Clone(GameObject* const newOwner) final { return new Transform(*this, newOwner); }
};