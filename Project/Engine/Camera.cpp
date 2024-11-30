#include "pch.h"
#include "Camera.h"
#include "Engine.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Material.h"

Camera::Camera(GameObject* const owner) 
	: Component(owner)
	, m_projType(PROJECTION_TYPE::ORTHOGRAPHIC)
	, m_near(1.f), m_far(500.f)
	, m_viewWidth(RESOLUTION.x), m_viewHeight(RESOLUTION.y)
	, m_fov(XM_PI / 2.f)
	, m_scale(1.f)
	, m_priority(RenderManager::GetInstance()->GetCameraCount())
{
	Init();
}

Camera::Camera(const Camera& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_projType(origin.m_projType)
	, m_near(origin.m_near), m_far(origin.m_far)
	, m_viewWidth(origin.m_viewWidth), m_viewHeight(origin.m_viewHeight)
	, m_fov(origin.m_fov)
	, m_scale(origin.m_scale)
	, m_priority(RenderManager::GetInstance()->GetCameraCount())
{
	Init();
}

Camera::~Camera()
{
	RenderManager::GetInstance()->DeleteCamera(this);
}

void Camera::Init()
{
	// 카메라 등록
	RenderManager::GetInstance()->AddCamera(this);
	CalcProjectionMatrix();
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
}

void Camera::Render()
{
	for (byte domain = 0; domain < SHADER_DOMAIN::DOMAIN_POST_PROCESS; ++domain)
	{
		for (const auto& pair : m_renderObjs[domain])
		{
			for (auto obj : pair.second)
			{
				obj->GetRenderComponent()->Render();
			}
		}
	}

	// Post Process Domain Shader
	for (const auto& pair : m_renderObjs[SHADER_DOMAIN::DOMAIN_POST_PROCESS])
	{
		for (auto obj : pair.second)
		{
			// TODO : RenderTarget 복사한 곳에 렌더링하도록 구현
			obj->GetRenderComponent()->Render();
		}
	}
}

void Camera::SetPriority(byte priority)
{
	if (m_priority == priority) return;
	RenderManager::GetInstance()->DeleteCamera(this);
	m_priority = priority;
	RenderManager::GetInstance()->AddCamera(this);
}

void Camera::AddRenderObject(GameObject* const obj)
{
	SHADER_DOMAIN domain = obj->GetRenderComponent()->GetMaterial()->GetShader()->GetShaderDomain();
#ifdef _DEBUG
	if (domain == SHADER_DOMAIN::DOMAIN_DEBUG)
	{
		MessageBox(nullptr, L"RenderManager::AddDebugRender() 를 통해 등록하세요", L"Camera::AddRenderObject() 실패", MB_OK);
		return;
	}
	if (domain == SHADER_DOMAIN_COUNT_END) assert(nullptr);
#endif // _DEBUG

	auto iter = m_renderObjs[domain].find(obj->GetLayer());

	if (iter != m_renderObjs[domain].end())
	{
#ifdef _DEBUG
		// 중복체크
		for (auto _obj : iter->second)
		{
			if (obj == _obj) assert(nullptr);
		}
#endif // _DEBUG

		iter->second.push_back(obj);
	}
	else
	{
		m_renderObjs[domain].insert(make_pair(obj->GetLayer(), vector<GameObject*>()));
		m_renderObjs[domain].find(obj->GetLayer())->second.push_back(obj);
	}
}

void Camera::DeleteRenderObject(GameObject* const obj)
{
	SHADER_DOMAIN domain = obj->GetRenderComponent()->GetMaterial()->GetShader()->GetShaderDomain();

#ifdef _DEBUG
	if (domain >= SHADER_DOMAIN_COUNT_END) assert(nullptr);
#endif // _DEBUG

	auto mapiter = m_renderObjs[domain].find(obj->GetLayer());
	if (mapiter != m_renderObjs[domain].end())
	{
		for (vector<GameObject*>::const_iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter)
		{
			if (obj == *iter)
			{
				mapiter->second.erase(iter);
				if (mapiter->second.empty()) m_renderObjs[domain].erase(mapiter);
				return;
			}
		}
	}
#ifdef _DEBUG
	else assert(nullptr);
#endif // _DEBUG
}