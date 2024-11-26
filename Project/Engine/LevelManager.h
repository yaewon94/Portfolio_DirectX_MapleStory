#pragma once
#include "GameObject.h"

// 레벨 관리 클래스
class LevelManager final : public Singleton<LevelManager>
{
	SINGLETON(LevelManager);

private:
	class Level* m_curLevel = nullptr;

public:
	int Init();
	void Tick();

public:
	// 오브젝트 생성 후, 현재 레벨에 자동으로 등록됨
	GameObject* const CreateObject(const string& name) { return new GameObject(name); }
	void RegisterObject(GameObject* const obj);
};