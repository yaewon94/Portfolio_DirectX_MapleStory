#include "pch.h"
#include "Camera.h"
#include "Engine.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"

Camera::Camera(GameObject* const owner) 
	: Component(owner)
	, m_projType(PROJECTION_TYPE::ORTHOGRAPHIC)
	, m_near(1.f), m_far(500.f)
	, m_viewWidth(RESOLUTION.x), m_viewHeight(RESOLUTION.y)
	, m_layers(ALL_LAYER_TYPES)	// 모든 레이어 렌더링
	, m_fov(XM_PI / 2.f)
	, m_scale(1.f)
	, m_priority(RenderManager::GetInstance()->GetCameraCount())
{
}

Camera::Camera(const Camera& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_projType(origin.m_projType)
	, m_near(origin.m_near), m_far(origin.m_far)
	, m_viewWidth(origin.m_viewWidth), m_viewHeight(origin.m_viewHeight)
	, m_layers(origin.m_layers)
	, m_fov(origin.m_fov)
	, m_scale(origin.m_scale)
	, m_priority(RenderManager::GetInstance()->GetCameraCount())
{
}

Camera::~Camera()
{
	for (const auto& vec : m_renderObjs)
	{
		for (auto obj : vec)
		{
			obj = nullptr;
		}
	}

	RenderManager::GetInstance()->DeleteCamera(this);
}

void Camera::Init()
{
	// 카메라 등록
	RenderManager::GetInstance()->AddCamera(this);
}

void Camera::FinalTick()
{
	// TODO : transform 값 변동 있을때만 호출하도록 구현
	Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
	Matrix matTrans = XMMatrixTranslation(-pos.x, -pos.y, -pos.z);

	Matrix matRot = XMMatrixIdentity();
	Vec3 right = GetOwner()->GetTransform()->GetWorldDirection(DIR_RIGHT);
	Vec3 up = GetOwner()->GetTransform()->GetWorldDirection(DIR_UP);
	Vec3 front = GetOwner()->GetTransform()->GetWorldDirection(DIR_FRONT);

	matRot._11 = right.x; matRot._12 = up.x; matRot._13 = front.x;
	matRot._21 = right.y; matRot._22 = up.y; matRot._23 = front.y;
	matRot._31 = right.z; matRot._32 = up.z; matRot._33 = front.z;

	g_tr.matView = matTrans * matRot;

	// 투영행렬 계산
	if (m_projType == PROJECTION_TYPE::ORTHOGRAPHIC)
	{
		g_tr.matProj = XMMatrixOrthographicLH((float)m_viewWidth/m_scale, (float)m_viewHeight/m_scale, m_near, m_far);
	}
	else // PROJECTION_TYPE::PERSPECTIVE
	{
		g_tr.matProj = XMMatrixPerspectiveFovLH(m_fov, m_viewHeight/m_viewWidth, m_near, m_far);
	}
}

void Camera::Render()
{
	for (byte domain = 0; domain < SHADER_DOMAIN::DOMAIN_POST_PROCESS; ++domain)
	{
		for (auto obj : m_renderObjs[domain])
		{
			if (m_layers & (1 << obj->GetLayer()))
			{
				obj->GetRenderComponent()->Render();
			}
		}
	}

	// Post Process Domain Shader
	for (auto obj : m_renderObjs[SHADER_DOMAIN::DOMAIN_POST_PROCESS])
	{
		if (m_layers & (1 << obj->GetLayer()))
		{
			// TODO : RenderTarget 복사한 곳에 렌더링
			obj->GetRenderComponent()->Render();
		}
	}
}

void Camera::AddRenderObject(GameObject* const obj)
{
	SHADER_DOMAIN domain = obj->GetRenderComponent()->GetMaterial()->GetShader()->GetShaderDomain();

#ifdef _DEBUG
	// 중복체크
	for (auto _obj : m_renderObjs[(size_t)domain])
	{
		if (_obj == obj) assert(nullptr);
	}
#endif // _DEBUG

	m_renderObjs[(size_t)domain].push_back(obj);
}

void Camera::SetPriority(byte priority)
{
	if (m_priority == priority) return;
	RenderManager::GetInstance()->DeleteCamera(this);
	m_priority = priority;
	RenderManager::GetInstance()->AddCamera(this);
}