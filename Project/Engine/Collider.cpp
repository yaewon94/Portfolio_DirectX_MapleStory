#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"

#ifdef _DEBUG
#include "RenderManager.h"
#include "AssetManager.h"
#include "Mesh.h"
#define COLOR_DEFAULT Vec4(0.f, 1.f, 0.f, 1.f)
#define COLOR_COLLISION Vec4(1.f, 0.f, 0.f, 1.f)
#endif // _DEBUG

Collider::Collider(GameObject* const owner) 
	: Component(owner)
	, m_offset(Vec2(0.f, 0.f)), m_scale(Vec2(1.f, 1.f))
{
	Init();
}

Collider::Collider(const Collider& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_offset(origin.m_offset), m_scale(origin.m_scale)
{
	Init();
}

Collider::~Collider()
{
	CollisionManager::GetInstance()->ResetCollisionState(GetOwner());

#ifdef _DEBUG
	RenderManager::GetInstance()->DeleteDebugRender(this);
#endif // _DEBUG
}

void Collider::Init()
{
#ifdef _DEBUG
	// 콜라이더 영역 표시되도록 RenderManager에 등록
	m_mesh = AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh_D");
	m_material = AssetManager::GetInstance()->FindAsset<Material>("Debug_Material");
	m_dbgColor = COLOR_DEFAULT;
	RenderManager::GetInstance()->AddDebugRender(this);
#endif // _DEBUG
}

void Collider::FinalTick()
{
	Matrix matScale = XMMatrixScaling(m_scale.x, m_scale.y, 1.f);
	Matrix matTrans = XMMatrixTranslation(m_offset.x, m_offset.y, 0.f);
	m_matWorld = matScale * matTrans * GetOwner()->GetTransform()->GetWorldMatrix();
}

void Collider::OnCollisionEnter(GameObject* const other)
{
#ifdef _DEBUG
	m_dbgColor = COLOR_COLLISION;
#endif // DEBUG

	GetOwner()->OnCollisionEnter(other);
}

void Collider::OnCollisionTick(GameObject* const other)
{
	GetOwner()->OnCollisionTick(other);
}

void Collider::OnCollisionExit(GameObject* const other)
{
#ifdef _DEBUG
	m_dbgColor = COLOR_DEFAULT;
#endif // DEBUG
	GetOwner()->OnCollisionExit(other);
}

void Collider::Render()
{
	// 좌표, 크기 바인딩
	ConstBuffer* cb = Device::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::TRANSFORM);
	g_tr.matWorld = m_matWorld;
	g_tr.matWV = g_tr.matWorld * g_tr.matView;
	g_tr.matWVP = g_tr.matWV * g_tr.matProj;
	cb->SetData(&g_tr);
	cb->Binding_GS();

	// material 바인딩
	m_material->GetConstBuffer().v4Arr[0] = m_dbgColor;
	m_material->Binding();

	// 렌더링
	m_mesh->Render();
}