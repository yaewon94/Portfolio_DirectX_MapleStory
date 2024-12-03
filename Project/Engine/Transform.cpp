#include "pch.h"
#include "Transform.h"
#include "Device.h"
#include "ConstBuffer.h"

const array<const Vec3, DIRECTION_TYPE_COUNT_END> Transform::UNIT_VEC
	= { Vec3(1.f, 0.f, 0.f)
	, Vec3(0.f, 1.f, 0.f)
	, Vec3(0.f, 0.f, 1.f) };

Transform::Transform(GameObject* const owner) 
	: Component(owner)
	, m_localScale(Vec3(100.f, 100.f, 1.f))
{
	Init();
}

Transform::Transform(const Transform& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_localPos(origin.m_localPos), m_localScale(origin.m_localScale), m_localRotation(origin.m_localRotation)
{
	Init();
}

Transform::~Transform()
{
}

void Transform::Init()
{
	OnChangeWorldMatrix(true);
}

void Transform::Binding()
{
	ConstBuffer* cb = Device::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::TRANSFORM);

	g_tr.matWorld = m_matWorld;
	g_tr.matWV = g_tr.matWorld * g_tr.matView;
	g_tr.matWVP = g_tr.matWV * g_tr.matProj;

	cb->SetData(&g_tr);
	cb->Binding_GS();
}

void Transform::OnChangeWorldMatrix(bool isChangedRotation)
{
	// 월드행렬 갱신
	Matrix matScale = XMMatrixScaling(m_localScale.x, m_localScale.y, m_localScale.z);
	Matrix matRotation = XMMatrixRotationX(m_localRotation.x) * XMMatrixRotationY(m_localRotation.y) * XMMatrixRotationZ(m_localRotation.z);
	Matrix matTrans = XMMatrixTranslation(m_localPos.x, m_localPos.y, m_localPos.z);
	m_matWorld = matScale * matRotation * matTrans;

	if (isChangedRotation)
	{
		// 방향벡터 갱신
		m_localDir[DIRECTION_TYPE::DIR_RIGHT] = Vec3(1.f, 0.f, 0.f);
		m_localDir[DIRECTION_TYPE::DIR_UP] = Vec3(0.f, 1.f, 0.f);
		m_localDir[DIRECTION_TYPE::DIR_FRONT] = Vec3(0.f, 0.f, 1.f);

		for (byte i = 0; i < DIRECTION_TYPE_COUNT_END; ++i)
		{
			m_worldDir[i] = m_localDir[i] = XMVector3TransformNormal(UNIT_VEC[i], matRotation);
		}
	}
}