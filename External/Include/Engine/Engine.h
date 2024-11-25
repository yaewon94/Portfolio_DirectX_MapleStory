#pragma once

enum class RESOLUTION_TYPE : byte
{
	FULL_HD
};

// ���ӿ��� ���� Ŭ����
class Engine final : public Singleton<Engine>
{
	SINGLETON(Engine)

private:
	HWND	m_hMainWnd;
	Vec2	m_resolution;

public:
	HWND GetMainWnd() const { return m_hMainWnd; }
	Vec2 GetResolution() const { return m_resolution; }

public:
	int Init(HWND hwnd);
	void Progress();
};

#define RESOLUTION Engine::GetInstance()->GetResolution()