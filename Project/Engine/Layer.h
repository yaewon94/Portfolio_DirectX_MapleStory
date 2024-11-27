#pragma once
#include "Entity.h"

typedef byte LAYER_TYPE;
#define MAX_LAYER 31

// LAYER_TYPE ���� ��Ʈ�����ڷ� ������ ��
// ���̾� �� ������ 0~31 �̹Ƿ� 32��Ʈ �������� Ÿ���� UINT�� ������
typedef UINT LAYER_TYPES;
#define ALL_LAYER_TYPES 0xffffffff

class GameObject;

// ���ӿ�����Ʈ�� ������ ����, ������ ���� ���� ����
class Layer final : public Entity
{
	friend class Level;

private:
	LAYER_TYPE m_idx;
	vector<GameObject*> m_objs;

private:
	Layer(LAYER_TYPE index);
	Layer(const Layer& origin);
	~Layer();
	Layer& operator=(const Layer& other);
	virtual Layer* Clone() final { return new Layer(*this); }

private:
	void Init();
	void Tick();
	void FinalTick();

private:
	void RegisterObject(GameObject* const obj);
};