#pragma once
#include "Component.h"
#include "IRenderable.h"
#include "Shader.h"
#include "Layer.h"
#include "Transform.h"

// ī�޶� ���� Ÿ��
enum class PROJECTION_TYPE : byte
{
	ORTHOGRAPHIC // ��������
	, PERSPECTIVE // ��������
};

// ī�޶� ������Ʈ
class Camera final : public Component
{
	NO_COPY_MOVE(Camera)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::CAMERA)

private:
	float m_near, m_far; // ������ ������ �ش�Ǵ� z�� �ּҰ�, �ִ밪
	float m_viewWidth, m_viewHeight; // �������� ����, ���� ũ��

	// �������� (PROJECTION_TYPE::PERSPECTIVE)
	float m_fov; // field of view (�þ߰�)

	// �������� (PROJECTION_TYPE::ORTHOGRAPHIC)
	float m_scale; // ���� ����

	array<map<LAYER_TYPE, vector<GameObject*>>, SHADER_DOMAIN_COUNT_END> m_renderObjs;

	LAYER_TYPES m_layers; // �������� ���̾� ����
	PROJECTION_TYPE m_projType;	// ���� Ÿ��
	byte m_priority;	// ������ ����

public:
	Camera(GameObject* const owner);
	Camera(const Camera& origin, GameObject* const newOwner);
	~Camera();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;
	virtual void FinalTick() final;

public:
	// TODO : RenderManager::Render() ������ ȣ���� �� �ְ�
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
		if (Near >= m_far) MessageBox(nullptr, L"near�� far���� �۾ƾ� �մϴ�", L"Change camera value is failed", MB_OK);
		else
		{
			m_near = Near;
			CalcProjectionMatrix();
		}
	}

	float GetFar() const { return m_far; }
	void SetFar(float Far)
	{
		if (Far <= m_near) MessageBox(nullptr, L"far�� near���� Ŀ�� �մϴ�", L"Change camera value is failed", MB_OK);
		else
		{
			m_far = Far;
			CalcProjectionMatrix();
		}
	}

	float GetViewWidth() const { return m_viewWidth; }
	void SetViewWidth(float width)
	{
		if (width <= 0.f) MessageBox(nullptr, L"width�� ������� �մϴ�", L"Change camera value is failed", MB_OK);
		else
		{
			m_viewWidth = width;
			CalcProjectionMatrix();
		}
	}

	float GetViewHeight() const { return m_viewHeight; }
	void SetViewHeight(float height)
	{
		if (height <= 0.f) MessageBox(nullptr, L"height�� ������� �մϴ�", L"Change camera value is failed", MB_OK);
		else
		{
			m_viewHeight = height;
			CalcProjectionMatrix();
		}
	}

	float GetFieldOfView() const { return m_fov; }
	// projection type : perspective�� ���� ��ȿ, @fov : 0 ~ 360
	void SetFieldOfView(int fov)
	{
		if (fov >= 0) fov %= 360;
		else fov = (fov % -360) + 360;
		m_fov = fov * XM_PI / 180.f;
		CalcProjectionMatrix();
	}

	float GetScale() const { return m_scale; }
	// projection type : orthographic�� ���� ��ȿ
	void SetScale(float scale)
	{
		if (scale <= 0.f) MessageBox(nullptr, L"ī�޶� �������� ������� �մϴ�", L"Change camera value is failed", MB_OK);
		else
		{
			m_scale = scale;
			CalcProjectionMatrix();
		}
	}

	LAYER_TYPES GetRenderLayers() const { return m_layers; }
	void SetLayerOnOff(LAYER_TYPE layer)
	{
		LAYER_TYPES checkBit = 1 << layer;

		// ��ϵ� ���̾��� ���
		if (m_layers & checkBit)
		{
			// ex. ???????1 & 00000001 => 00000001
			// layer ��Ʈ���� 11111110
			// ???????1 & 11111110 => #######0
			// ? ��Ʈ�� ��ġ�� ���̾ ��ϵǾ� �ִ� ���� ������ #���� 1�� ������,
			// ��ϵǾ� ���� ���� ���� #���� 0�� �ǹǷ� �ٸ� ���̾� ���� ������ ���� ����
			m_layers &= ~checkBit;
		}
		// ��ϵ��� ���� ���
		else
		{
			// ex. ???????0 | 00000001 => ???????1
			m_layers |= checkBit;
		}
	}

	void AddRenderObject(GameObject* const obj);

	byte GetPriority() const { return m_priority; }
	void SetPriority(byte priority);
	
private:
	void CalcProjectionMatrix()
	{
		if (m_projType == PROJECTION_TYPE::ORTHOGRAPHIC) g_tr.matProj = XMMatrixOrthographicLH((float)m_viewWidth / m_scale, (float)m_viewHeight / m_scale, m_near, m_far);
		else if (m_projType == PROJECTION_TYPE::PERSPECTIVE) g_tr.matProj = XMMatrixPerspectiveFovLH(m_fov, m_viewHeight / m_viewWidth, m_near, m_far);
#ifdef _DEBUG
		else assert(nullptr);
#endif // _DEBUG
	}

private: // GameObject::��������� ���� ȣ��
	virtual Camera* Clone(GameObject* const newOwner) final { return new Camera(*this, newOwner); }
};