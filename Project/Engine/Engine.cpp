#include "pch.h"
#include "Engine.h"
#include "Device.h"
#include "AssetManager.h"
#include "KeyManager.h"
#include "LevelManager.h"
#include "PathManager.h"
#include "TimeManager.h"

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

	// 윈도우 초기화
	RECT rt = { 0, 0, m_resolution.x , m_resolution.y };
	if (!AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!GetMenu(m_hMainWnd)))
	{
		MessageBoxA(nullptr, "AdjustWindowRect returns false", "Initialize Engine is failed", MB_OK);
		return E_FAIL;
	}
	if (!SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0))
	{
		MessageBoxA(nullptr, "SetWindowPos returns false", "Initialize Engine is failed", MB_OK);
		return E_FAIL;
	}

	// Device 초기화
	if (FAILED(Device::GetInstance()->Init())) return E_FAIL;

	// Manager 클래스들 초기화
	TimeManager::GetInstance()->Init();
	PathManager::GetInstance()->Init();
	if (FAILED(AssetManager::GetInstance()->Init())) return E_FAIL;
	if (FAILED(LevelManager::GetInstance()->Init())) return E_FAIL;

	return S_OK;
}

void Engine::Progress()
{
	// Manager 클래스들 Tick() 호출
	TimeManager::GetInstance()->Tick();
	KeyManager::GetInstance()->Tick();
	LevelManager::GetInstance()->Tick();
}