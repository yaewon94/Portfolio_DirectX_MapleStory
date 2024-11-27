#pragma once
#include "Entity.h"

class GameObject;

// 컴포넌트 타입
enum class COMPONENT_TYPE : byte
{
	TRANSFORM, CAMERA, MESH_RENDER, SCRIPT
};

#define COMPONENT_TYPE_DCL(type) public:\
									static constexpr COMPONENT_TYPE Type = type;\
									inline virtual COMPONENT_TYPE GetType() final { return Type; }

// 게임오브젝트 동작에 관한 요소들의 최상위 클래스
class Component : public Entity
{
	NO_COPY_MOVE(Component);

protected:
	friend class GameObject;
	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;

private:
	GameObject* m_owner;

protected:
	Component(GameObject* const owner);
	Component(const Component& origin, GameObject* const newOwner);
	~Component();
	virtual Component* Clone(GameObject* const newOwner) = 0;

protected:
	inline virtual COMPONENT_TYPE GetType() = 0;

protected:
	virtual void Init() {}
	virtual void FinalTick() = 0;

protected:
	GameObject* const GetOwner() { return m_owner; }

private:
	virtual Entity* Clone() final { return nullptr; } // delete
};