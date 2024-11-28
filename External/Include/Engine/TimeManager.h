#pragma once

class TimeManager final : public Singleton<TimeManager>
{
	SINGLETON(TimeManager);

private:
	LARGE_INTEGER m_frequency;	// 초당 카운트
	LARGE_INTEGER m_currentCount; // 현재 카운팅
	LARGE_INTEGER m_prevCount; // 이전 프레임 카운팅

	float m_deltaTime; // 프레임 당 시간
	UINT m_fps; // 초당 프레임 수

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime() const { return m_deltaTime; }
};

#define DT TimeManager::GetInstance()->GetDeltaTime()