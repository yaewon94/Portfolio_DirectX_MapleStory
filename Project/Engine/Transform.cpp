#include "pch.h"
#include "Transform.h"

Transform::Transform(GameObject* const owner) 
	: Component(owner)
	, m_localScale(Vec3(100.f, 100.f, 1.f))
{
}

Transform::Transform(const Transform& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_localPos(origin.m_localPos), m_localScale(origin.m_localScale), m_localRotation(origin.m_localRotation)
{
}

Transform::~Transform()
{

}

void Transform::FinalTick()
{
	m_matWorld = XMMatrixIdentity();

	Matrix matScale = XMMatrixScaling(m_localScale.x, m_localScale.y, m_localScale.z);
	Matrix matRotation = XMMatrixRotationX(m_localRotation.x) * XMMatrixRotationY(m_localRotation.y) * XMMatrixRotationZ(m_localRotation.z);
	Matrix matTrans = XMMatrixTranslation(m_localPos.x, m_localPos.y, m_localPos.z);

	// 크기 * 회전 * 이동
	m_matWorld = matScale * matRotation * matTrans;
}

void Transform::Binding()
{
}