#pragma once
#include "Engine/Script.h"

// ���� ������Ʈ
class Ground final : public Script
{
	NO_COPY_MOVE(Ground)

public:
	Ground(GameObject* const owner);
	Ground(const Ground& origin, GameObject* const newOwner);
	~Ground();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;

private:
	virtual Ground* Clone(GameObject* const newOwner) final { return new Ground(*this, newOwner); }
};