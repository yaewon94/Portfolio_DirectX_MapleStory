#pragma once
#include "Component.h"
#include "IDebugRenderable.h"

class GameObject;

// ���ӿ�����Ʈ���� �浹�� �Ǻ��ϱ� ���� ������Ʈ
#ifdef _DEBUG
class Collider final : public Component, public IDebugRenderable
#elif
class Collider final : public Component
#endif // _DEBUG
{
	NO_COPY_MOVE(Collider)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::COLLIDER)
	friend class CollisionManager;

private:
	Vec2 m_offset;
	Vec2 m_scale; // ���ӿ�����Ʈ ũ�⿡ ���� ����
	Matrix m_matWorld;
	bool m_isActive;

public:
	Collider(GameObject* const owner);
	Collider(const Collider& origin, GameObject* const newOwner);
	~Collider();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;
	virtual void FinalTick() final;

private: // CollisionManager���� ȣ��
	void OnCollisionEnter(GameObject* const other);
	void OnCollisionTick(GameObject* const other);
	void OnCollisionExit(GameObject* const other);
	const Matrix& GetWorldMatrix() const { return m_matWorld; }

public:
	virtual void SetActive(bool flag) final;
	bool IsActive() const { return m_isActive; }

	Vec2 GetOffset() const { return m_offset; }
	void SetOffset(Vec2 offset) { m_offset = offset; }

	Vec2 GetScale() const { return m_scale; }
	void SetScale(Vec2 scale) { m_scale = scale; }

private: // GameObject::��������� ���� ȣ��
	virtual Collider* Clone(GameObject* const newOwner) final { return new Collider(*this, newOwner); }

#ifdef _DEBUG
private:
	SharedPtr<class Material> m_material;
	SharedPtr<class Mesh> m_mesh;
	Vec4 m_dbgColor;
	virtual void Render() final;
#endif // _DEBUG
};