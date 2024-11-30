#pragma once
#include "GameObject.h"
#include "Level.h"

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
	GameObject* const FindObject(const UINT ID) const { return m_curLevel->FindObject(ID); }
	const vector<GameObject*>& GetObjects(OBJECT_TAG tag) const { return m_curLevel->GetObjects(tag); }

	// ������Ʈ ���� ��, ���� ������ �ڵ����� ��ϵ�
	GameObject* const CreateObject(const string& name) { return new GameObject(name); }
	void RegisterObject(GameObject* const obj) { m_curLevel->RegisterObject(obj); }
	void DeleteObject(GameObject* const obj) { m_curLevel->DeleteObject(obj); }
};