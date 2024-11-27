#pragma once
#include "Engine/Script.h"
#include "Engine/KeyManager.h"

// �÷��̾� ������Ʈ
class Player final : public Script, public IKeyEvent
{
	NO_COPY_MOVE(Player)

public:
	Player(GameObject* const owner);
	Player(const Player& origin, GameObject* const newOwner);
	~Player();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;
	virtual void Tick() final {}

private: // KeyManager : IKeyEvent* �� ���� ȣ��
	void Move(KEY_CODE key);

private:
	virtual Player* Clone(GameObject* const newOwner) final { return new Player(*this, newOwner); }
};