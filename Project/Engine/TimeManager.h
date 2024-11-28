#pragma once

class TimeManager final : public Singleton<TimeManager>
{
	SINGLETON(TimeManager);

private:
	LARGE_INTEGER m_frequency;	// �ʴ� ī��Ʈ
	LARGE_INTEGER m_currentCount; // ���� ī����
	LARGE_INTEGER m_prevCount; // ���� ������ ī����

	float m_deltaTime; // ������ �� �ð�
	UINT m_fps; // �ʴ� ������ ��

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime() const { return m_deltaTime; }
};

#define DT TimeManager::GetInstance()->GetDeltaTime()