#pragma once
#include "Component.h"
#include "IRenderable.h"
#include "RenderValues.h"
#include "Shader.h"
#include "Transform.h"

// 카메라 투영 타입
enum class PROJECTION_TYPE : byte
{
	ORTHOGRAPHIC // 직교투영
	, PERSPECTIVE // 원근투영
};

// 카메라 컴포넌트
class Camera final : public Component
{
	NO_COPY_MOVE(Camera)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::CAMERA)

private:
	float m_near, m_far; // 렌더링 범위에 해당되는 z축 최소값, 최대값
	float m_viewWidth, m_viewHeight; // 렌더링할 가로, 세로 크기

	// 원근투영 (PROJECTION_TYPE::PERSPECTIVE)
	float m_fov; // field of view (시야각)

	// 직교투영 (PROJECTION_TYPE::ORTHOGRAPHIC)
	float m_scale; // 투영 배율

	array<map<LAYER, vector<GameObject*>>, SHADER_DOMAIN_COUNT_END> m_renderObjs;

	PROJECTION_TYPE m_projType;	// 투영 타입
	byte m_priority;	// 렌더링 순서

public:
	Camera(GameObject* const owner);
	Camera(const Camera& origin, GameObject* const newOwner);
	~Camera();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;
	virtual void FinalTick() final;

public:
	// TODO : RenderManager::Render() 에서만 호출할 수 있게
	void Render();

public:
	PROJECTION_TYPE GetProjectionType() const { return m_projType; }
	void SetProjectionType(PROJECTION_TYPE type)
	{ 
		m_projType = type;
		CalcProjectionMatrix();
	}

	float GetNear() const { return m_near; }
	void SetNear(float Near)
	{
		if (Near >= m_far) MessageBox(nullptr, L"near은 far보다 작아야 합니다", L"Change camera value is failed", MB_OK);
		else
		{
			m_near = Near;
			CalcProjectionMatrix();
		}
	}

	float GetFar() const { return m_far; }
	void SetFar(float Far)
	{
		if (Far <= m_near) MessageBox(nullptr, L"far은 near보다 커야 합니다", L"Change camera value is failed", MB_OK);
		else
		{
			m_far = Far;
			CalcProjectionMatrix();
		}
	}

	float GetViewWidth() const { return m_viewWidth; }
	void SetViewWidth(float width)
	{
		if (width <= 0.f) MessageBox(nullptr, L"width는 양수여야 합니다", L"Change camera value is failed", MB_OK);
		else
		{
			m_viewWidth = width;
			CalcProjectionMatrix();
		}
	}

	float GetViewHeight() const { return m_viewHeight; }
	void SetViewHeight(float height)
	{
		if (height <= 0.f) MessageBox(nullptr, L"height는 양수여야 합니다", L"Change camera value is failed", MB_OK);
		else
		{
			m_viewHeight = height;
			CalcProjectionMatrix();
		}
	}

	float GetFieldOfView() const { return m_fov; }
	// projection type : perspective일 때만 유효, @fov : 0 ~ 360
	void SetFieldOfView(int fov)
	{
		if (fov >= 0) fov %= 360;
		else fov = (fov % -360) + 360;
		m_fov = fov * XM_PI / 180.f;
		CalcProjectionMatrix();
	}

	float GetScale() const { return m_scale; }
	// projection type : orthographic일 때만 유효
	void SetScale(float scale)
	{
		if (scale <= 0.f) MessageBox(nullptr, L"카메라 배율값은 양수여야 합니다", L"Change camera value is failed", MB_OK);
		else
		{
			m_scale = scale;
			CalcProjectionMatrix();
		}
	}

	byte GetPriority() const { return m_priority; }
	void SetPriority(byte priority);

	void AddRenderObject(GameObject* const obj);
	void DeleteRenderObject(GameObject* const obj);
	
private:
	void CalcProjectionMatrix()
	{
		if (m_projType == PROJECTION_TYPE::ORTHOGRAPHIC) g_tr.matProj = XMMatrixOrthographicLH((float)m_viewWidth / m_scale, (float)m_viewHeight / m_scale, m_near, m_far);
		else if (m_projType == PROJECTION_TYPE::PERSPECTIVE) g_tr.matProj = XMMatrixPerspectiveFovLH(m_fov, m_viewHeight / m_viewWidth, m_near, m_far);
#ifdef _DEBUG
		else assert(nullptr);
#endif // _DEBUG
	}

private: // GameObject::복사생성자 에서 호출
	virtual Camera* Clone(GameObject* const newOwner) final { return new Camera(*this, newOwner); }
};