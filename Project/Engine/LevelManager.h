#pragma once

class GameObject;

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
	void AddObject(GameObject* const obj);
};