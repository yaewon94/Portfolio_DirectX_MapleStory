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

extern CB_Transform g_tr;

// 게임오브젝트 좌표, 크기, 각도 정보
class Transform final : public Component
{
	NO_COPY_MOVE(Transform)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::TRANSFORM)

private:
	Vec3 m_localPos, m_localScale, m_localRotation;
	Matrix m_matWorld;

public:
	Transform(GameObject* const owner);
	Transform(const Transform& origin, GameObject* const newOwner);
	~Transform();
public:
	virtual void FinalTick() final;

public:
	void Binding();

private:
	virtual Transform* Clone(GameObject* const newOwner) final { return new Transform(*this, newOwner); }
};