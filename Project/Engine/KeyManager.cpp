#include "pch.h"
#include "KeyManager.h"
#include "Engine.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::Init()
{
	AddKey(KEY_LEFT);
	AddKey(KEY_RIGHT);
}

void KeyManager::Tick()
{
	// 윈도우가 포커싱 중일때
	if (Engine::GetInstance()->IsFocused())
	{
		for (auto& key : m_keyMap)
		{
			// 이번 프레임에 해당 키가 눌림
			if (GetAsyncKeyState(key.first) & 0x8001)
			{
				if (key.second == KEY_STATE::NONE) key.second = KEY_STATE::TAP;
				else if (key.second == KEY_STATE::TAP) key.second = KEY_STATE::DOWN;

				// TODO : 각각 KEY마다 호출하는 함수 일반화 하기
			}
			// 안눌림
			else
			{
				if (key.second == KEY_STATE::TAP || key.second == KEY_STATE::DOWN) key.second = KEY_STATE::RELEASED;
				else if (key.second == KEY_STATE::RELEASED) key.second = KEY_STATE::NONE;
			}
		}
	}
	// 윈도우가 포커싱 중이 아님
	else
	{
		for (auto& key : m_keyMap)
		{
			key.second = KEY_STATE::NONE;
		}
	}
}