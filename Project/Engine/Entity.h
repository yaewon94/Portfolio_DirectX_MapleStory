#pragma once

// 게임오브젝트, 컴포넌트, 에셋 등의 최상위 클래스
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