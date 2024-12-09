#pragma once
#include "Engine/Script.h"

// 플레이어, 몬스터 등 상태를 가지고 있고, 이동가능, 스킬사용가능 등의 특징을 가진 오브젝트
class AliveObject : public Script
{
	NO_COPY_MOVE(AliveObject)

protected:
	class FlipbookPlayer* m_flipbookPlayer;

protected:
	AliveObject(GameObject* const owner);
	AliveObject(const AliveObject& origin, GameObject* const newOwner);
	~AliveObject();

public:
	FlipbookPlayer* const GetFlipbookPlayer() const { return m_flipbookPlayer; }
};