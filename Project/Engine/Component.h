#pragma once
#include "Entity.h"

class GameObject;

// ������Ʈ Ÿ��
enum class COMPONENT_TYPE : byte
{

};

#define COMPONENT_TYPE_DCL(type) public:\
									static constexpr COMPONENT_TYPE Type = type;\
									inline virtual COMPONENT_TYPE GetType() final { return Type; }

// ���ӿ�����Ʈ ���ۿ� ���� ��ҵ��� �ֻ��� Ŭ����
class Component : public Entity
{
	NO_COPY_MOVE(Component);
	friend class GameObject;

private:
	GameObject* m_owner;

protected:
	Component(GameObject* const owner);
	~Component();
	virtual Component* Clone() override = 0;

protected:
	inline virtual COMPONENT_TYPE GetType() = 0;

protected:
	virtual void Init() {}
	virtual void FinalTick() = 0;
};