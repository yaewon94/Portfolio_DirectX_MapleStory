#pragma once
#include "Engine/Script.h"
#include "IMovable.h"

// �÷��̾�, ���� �� ���¸� ������ �ְ�, �̵�����, ��ų��밡�� ���� Ư¡�� ���� ������Ʈ
class AliveObject : public Script, public IMovable
{
	NO_COPY_MOVE(AliveObject)

protected:
	class FlipbookPlayer* m_flipbookPlayer;
	class FSM* m_fsm;

protected:
	AliveObject(GameObject* const owner);
	AliveObject(const AliveObject& origin, GameObject* const newOwner);
	~AliveObject();

protected: // GameObject : Component* �� ���� ȣ��
	virtual void Init() override;

public:
	FlipbookPlayer* const GetFlipbookPlayer() const { return m_flipbookPlayer; }
	FSM* const GetFSM() const { return m_fsm; }
};