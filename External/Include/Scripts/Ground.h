#pragma once
#include "Engine/Script.h"

// 발판 컴포넌트
class Ground final : public Script
{
	NO_COPY_MOVE(Ground)

public:
	Ground(GameObject* const owner);
	Ground(const Ground& origin, GameObject* const newOwner);
	~Ground();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;

private:
	virtual Ground* Clone(GameObject* const newOwner) final { return new Ground(*this, newOwner); }
};