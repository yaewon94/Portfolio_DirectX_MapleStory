#pragma once

class GameObject;

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
	void AddObject(GameObject* const obj);
};