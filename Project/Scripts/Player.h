#pragma once
#include "Engine/Script.h"
#include "Engine/KeyManager.h"

// 플레이어 컴포넌트
class Player final : public Script, public IKeyEvent
{
	NO_COPY_MOVE(Player)

public:
	Player(GameObject* const owner);
	Player(const Player& origin, GameObject* const newOwner);
	~Player();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;
	virtual void Tick() final {}

private: // KeyManager : IKeyEvent* 를 통해 호출
	void Move(KEY_CODE key);

private:
	virtual Player* Clone(GameObject* const newOwner) final { return new Player(*this, newOwner); }
};