#include "pch.h"
#include "TimeManager.h"
#include "Device.h"
#ifdef _DEBUG
#include "Engine.h"
#endif // _DEBUG


TimeManager::TimeManager()
	: m_frequency{}
	, m_currentCount{}, m_prevCount{}
	, m_deltaTime(0.f)
	, m_fps(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_prevCount);
}

void TimeManager::Tick()
{
	static float accTime = 0.f;

	QueryPerformanceCounter(&m_currentCount);

	// deltaTime 계산, 보정
	m_deltaTime = (m_currentCount.QuadPart - m_prevCount.QuadPart) / (float)m_frequency.QuadPart;
	if (m_deltaTime > Device::GetInstance()->GetRefreshRateDT()) m_deltaTime = Device::GetInstance()->GetRefreshRateDT();

	// 시간 누적
	accTime += m_deltaTime;

	// fps 누적
	++m_fps;

	if (accTime >= 1.f)
	{
#ifdef _DEBUG
		Engine::GetInstance()->SetText(std::to_string(m_fps).c_str());
#endif // _DEBUG
		accTime -= 1.f;
		m_fps = 0;
	}

	m_prevCount = m_currentCount;
}