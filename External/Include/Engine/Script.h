#pragma once
#include "Component.h"

// 커스텀 스크립트 최상위 클래스
class Script : public Component
{
	NO_COPY_MOVE(Script)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::SCRIPT)
	friend class GameObject;

public:
	Script(GameObject* const owner);
	Script(const Script& origin, GameObject* const newOwner);
	~Script();

private: // GameObject : Component* 를 통해 호출
	virtual void Tick() {}
	virtual void FinalTick() override {}

private:
	virtual Script* Clone(GameObject* const newOwner) override = 0;
};