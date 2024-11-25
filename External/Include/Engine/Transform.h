#pragma once
#include "Component.h"

struct CB_Transform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;

	Matrix	matWV; // world * view
	Matrix	matWVP; // world * view * projection
};

// ���ӿ�����Ʈ ��ǥ, ũ��, ���� ����
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
	virtual Component* Clone(GameObject* const newOwner) final { return new Transform(*this, newOwner); }

public:
	virtual void FinalTick() final;

public:
	void Binding();
};