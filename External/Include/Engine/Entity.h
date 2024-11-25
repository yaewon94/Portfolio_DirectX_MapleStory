#pragma once

// ���ӿ�����Ʈ, ������Ʈ, ���� ���� �ֻ��� Ŭ����
class Entity
{
private:
	static UINT nextID;

private:
	const UINT m_ID;

protected:
	Entity();
	Entity(const Entity& origin);
	virtual ~Entity();

public:
	UINT GetID() const { return m_ID; }

public:
	virtual Entity* Clone() = 0;
};