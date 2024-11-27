#pragma once
#include "Entity.h"

typedef byte LAYER_TYPE;
#define MAX_LAYER 31

// LAYER_TYPE 들을 비트연산자로 조합한 값
// 레이어 값 범위가 0~31 이므로 32비트 양의정수 타입인 UINT로 설정함
typedef UINT LAYER_TYPES;
#define ALL_LAYER_TYPES 0xffffffff

class GameObject;

// 게임오브젝트의 렌더링 순서, 렌더링 여부 등을 결정
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