#pragma once
#include "Entity.h"

class GameObject;

// ���ӿ�����Ʈ�� ������ ����, ������ ���� ���� ����
class Layer final : public Entity
{
private:
	vector<GameObject*> m_objs;

public:
	Layer();
	Layer(const Layer& origin);
	~Layer();
	Layer& operator=(const Layer& other);
	virtual Layer* Clone() final { return new Layer(*this); }

public:
	void Init();
	void Tick();
	void FinalTick();
};

#define MAX_LAYER 32