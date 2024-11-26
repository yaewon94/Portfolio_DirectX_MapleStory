#pragma once
#include "GameObject.h"

// ���� ���� Ŭ����
class LevelManager final : public Singleton<LevelManager>
{
	SINGLETON(LevelManager);

private:
	class Level* m_curLevel = nullptr;

public:
	int Init();
	void Tick();

public:
	// ������Ʈ ���� ��, ���� ������ �ڵ����� ��ϵ�
	GameObject* const CreateObject(const string& name) { return new GameObject(name); }
	void RegisterObject(GameObject* const obj);
};