#pragma once
#include "Entity.h"

class GameObject;

// ���ӿ�����Ʈ�� ������ ����, ������ ���� ���� ����
class Layer final : public Entity
{
	NO_COPY_MOVE(Layer);

private:
	vector<GameObject*> m_objs;

public:
	Layer();
	~Layer();

public:
	void Init();
	void Tick();
	void FinalTick();

private:
	virtual Entity* Clone() final { return nullptr; } // delete
};

#define MAX_LAYER 32