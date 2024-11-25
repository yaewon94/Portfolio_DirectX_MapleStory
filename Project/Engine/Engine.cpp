#include "pch.h"
#include "Engine.h"

Vec2 resolution_type_arr[] = {Vec2(1920, 1080)};

Engine::Engine()
	: m_hMainWnd(nullptr)
{
}

Engine::~Engine()
{
}

int Engine::Init(HWND hwnd)
{
	m_hMainWnd = hwnd;
	m_resolution = resolution_type_arr[(size_t)RESOLUTION_TYPE::FULL_HD];

	RECT rt = { 0, 0, m_resolution.x , m_resolution.y };
	if (!AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!GetMenu(m_hMainWnd)))
	{
		MessageBoxA(nullptr, "AdjustWindowRect returns false", "Init Engine is failed", 0);
		return E_FAIL;
	}
	if (!SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0))
	{
		MessageBoxA(nullptr, "SetWindowPos returns false", "Init Engine is failed", 0);
		return E_FAIL;
	}

	return S_OK;
}

void Engine::Progress()
{
}