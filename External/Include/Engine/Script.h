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

	virtual void OnCollisionEnter(GameObject* other) {}
	virtual void OnCollisionTick(GameObject* other) {}
	virtual void OnCollisionExit(GameObject* other) {}

private:
	virtual Script* Clone(GameObject* const newOwner) override = 0;
};