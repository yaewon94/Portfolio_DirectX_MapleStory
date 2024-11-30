#pragma once
#include "Component.h"

// Ŀ���� ��ũ��Ʈ �ֻ��� Ŭ����
class Script : public Component
{
	NO_COPY_MOVE(Script)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::SCRIPT)
	friend class GameObject;

public:
	Script(GameObject* const owner);
	Script(const Script& origin, GameObject* const newOwner);
	~Script();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Tick() {}
	virtual void FinalTick() override {}

private:
	virtual Script* Clone(GameObject* const newOwner) override = 0;
};