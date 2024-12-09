#pragma once
#include "Engine/Script.h"

// �÷��̾�, ���� �� ���¸� ������ �ְ�, �̵�����, ��ų��밡�� ���� Ư¡�� ���� ������Ʈ
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