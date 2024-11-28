#include "pch.h"
#include "KeyManager.h"
#include "Engine.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
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
				key.second.state = KEY_STATE::DOWN;
				key.second.instance->OnKeyDown(key.first);
			}
			// 안눌림
			else
			{
				if (key.second.state == KEY_STATE::DOWN) key.second.state = KEY_STATE::RELEASED;
				else if (key.second.state == KEY_STATE::RELEASED) key.second.state = KEY_STATE::NONE;
			}
		}
	}
	// 윈도우가 포커싱 중이 아님
	else
	{
		for (auto& key : m_keyMap)
		{
			key.second.state = KEY_STATE::NONE;
		}
	}
}