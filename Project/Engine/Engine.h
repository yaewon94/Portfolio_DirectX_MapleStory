#pragma once

enum class RESOLUTION_TYPE : byte
{
	FULL_HD
};

// 게임엔진 관리 클래스
class Engine final : public Singleton<Engine>
{
	SINGLETON(Engine)

private:
	HWND m_hMainWnd;
	Vec2 m_resolution;
	bool m_isQuit;

public:
	HWND GetMainWnd() const { return m_hMainWnd; }
	Vec2 GetResolution() const { return m_resolution; }

public:
	int Init(HWND hwnd);
	void Progress();
	void Quit();

public:
	bool IsFocused() const { return m_hMainWnd == GetFocus(); }
	bool IsQuit() const { return m_isQuit; }

#ifdef _DEBUG
public:
	void SetText(const char* text) { SetWindowTextA(m_hMainWnd, text); }
#endif // _DEBUG
};

#define RESOLUTION Engine::GetInstance()->GetResolution()